#include "VulkanManager.hpp"
#include "../../Log.hpp"
#include "Error.hpp"

namespace Animus::Vulkan {
    Version convertVersion(uint32_t version) {
        uint32_t major = (version >> 22) & 0x3FF;
        uint32_t minor = (version >> 12) & 0x3FF;
        uint32_t patch = version & 0xFFF;

        return Version(major, minor, patch);
    }

    VulkanManager::VulkanManager(void) {
        UnsafeVector<const char*> layers;
        UnsafeVector<const char*> extensions;

        vk::InstanceCreateInfo info;
        vk::ApplicationInfo appInfo;

        //open vulkan library and load basic functions
        #ifdef _WIN32
            this->so = SharedObject_::cretae("vulkan-1.dll");
        #elif defined(__linux__)
            this->so = SharedObject_::create("libvulkan.so");
        #endif
        vkGetInstanceProcAddr = this->so->loadFunction<PFN_vkVoidFunction(VkInstance, const char*)>("vkGetInstanceProcAddr");
        this->loadBaseFunctions();

        #ifdef DEBUG
            if(this->hasLayer("VK_LAYER_LUNARG_standard_validation")) {
                layers.push_back("VK_LAYER_LUNARG_standard_validation");
            }
            else {
                Log::getSingleton().warnStr("Vulkan instance does not support VK_LAYER_LUNARG_standard_validation");
            }
        #endif

        extensions = this->getPlatformExtensions();

        info.enabledLayerCount = layers.size();
        info.ppEnabledLayerNames = &layers[0];

        info.enabledExtensionCount = extensions.size();
        info.ppEnabledExtensionNames = &extensions[0];

        this->instance = vk::createInstance(info);
        this->instanceDispatch = vk::DispatchLoaderDynamic(this->instance);

        //it's not likely that we're going to need this info any more, free up some memory
        this->instanceLayers.clear();
        this->instanceExtensions.clear();

        this->createDevice();
    }

    VulkanManager::~VulkanManager(void) {
        //Clear this pointer so that the sharedobject will release
        vkGetInstanceProcAddr.destroy();
    }

    void VulkanManager::loadBaseFunctions(void) {
        vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(vkGetInstanceProcAddr(nullptr, "vkCreateInstance"));
        vkEnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties"));
        vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties"));
        vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
    }

    void VulkanManager::createDevice(void) {
        UnsafeVector<vk::PhysicalDevice> physicalDevices;
        UnsafeVector<vk::PhysicalDeviceGroupProperties> physicalDeviceGroups;
        Optional<uint32_t> deviceIndex;
        Optional<uint32_t> groupIndex;
        Optional<uint32_t> maxGroupScore;
        Optional<uint32_t> maxDeviceScore;

        if(this->getVersion() >= Version(1, 1, 0)) {
            physicalDeviceGroups = this->instance.enumeratePhysicalDeviceGroups(this->instanceDispatch);
        }

        physicalDevices = this->instance.enumeratePhysicalDevices(this->instanceDispatch);

        //find the device group with the highest score
        if(physicalDeviceGroups.size() > 0) {
            for(int i = 0; i < physicalDeviceGroups.size(); i++) {
                int score = VulkanManager::calculateDeviceScore(physicalDeviceGroups[i]);

                if(score > maxGroupScore) {
                    maxGroupScore = score;
                    groupIndex = i;
                }
            }
        }

        //find the device with the highest score
        for(int i = 0; i < physicalDevices.size(); i++) {
            int score = VulkanManager::calculateDeviceScore(physicalDevices[i]);

            if(score > maxDeviceScore) {
                maxDeviceScore = score;
                deviceIndex = i;
            }
        }

        if(!maxGroupScore.has_value() && !maxDeviceScore.has_value()) {
            Log::getSingleton().errorStr("Falied to find suitable Vulkan device");
            throw NoSuitableDevice();
        }

        //a single device winning out is rare, but could happen
        /*if(maxDeviceScore > maxGroupScore) {
            if(deviceIndex.has_value()) {
                this->createSingleDevice(physicalDevices[deviceIndex.value()]);
            }
            else {
                if(groupIndex.has_value()) {
                    this->createGroupDevice(physicalDeviceGroups[groupIndex.value()])
                }
                else {
                    Log::getSingleton().errorStr("Failed to create device");
                }
            }
        }
        else
        if(maxDeviceScore == maxGroupScore) {
            //prefer a group if we have it
            if(groupIndex.has_value()) {
                this->createGroupDevice(physicalDeviceGroups[groupIndex.has_value()]);
            }
            else {
                if(deviceIndex.has_value()) {
                    this->createSingleDevice(physicalDevices[deviceIndex.has_value()]);
                }
                else {
                    Log::getSingleton().errorStr("Failed to find device");
                }
            }
        }
        else {
            if(deviceIndex.has_value()) {
                this->createSingleDevice(physicalDevices[deviceIndex.value()]);
            }
            else {
                if(groupIndex.has_value()) {
                    this->createGroupDevice(physicalDeviceGroups[groupIndex.value()])
                }
                else {
                    Log::getSingleton().errorStr("Failed to create device");
                }
            }
        }*/
    }

    uint32_t VulkanManager::calculateDeviceScore(const vk::PhysicalDevice& device) {
        auto properties = device.getProperties(this->instanceDispatch);
        auto queueProps = device.getQueueFamilyProperties(this->instanceDispatch);
        vk::QueueFlags gtcBits = vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eTransfer;
        vk::QueueFlags gtBits = vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eTransfer;
        vk::QueueFlags ctBits = vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eTransfer;
        uint32_t score = 0;
        uint32_t gtCount = 0;
        uint32_t ctCount = 0;
        uint32_t gtcCount = 0;

        switch (properties.deviceType) {
            case vk::PhysicalDeviceType::eDiscreteGpu:
                score += 16;
                break;

            case vk::PhysicalDeviceType::eVirtualGpu:
                score += 12;
                break;

            case vk::PhysicalDeviceType::eIntegratedGpu:
                score += 8;

            default:
                //nothing for other types
                break;
        }

        //ideally, we'd want at least one of the following queue families
        //COMPUTE | TRANSFER
        //GRAPHICS | TRANSFER
        //this ensures that we could handle graphics and computer seperately
        //But we'll work with any combination that allows at least one graphics,
        //compute and transfer queue

        for(auto& prop: queueProps) {
            uint32_t count = prop.queueCount;
            if(prop.queueFlags & gtcBits) {
                gtcCount += count;
                score += gtcCount * 12;
            }
            else
            if(prop.queueFlags & gtBits) {
                gtCount += count;
                score += gtCount * 16;
            }
            else
            if(prop.queueFlags & ctBits) {
                ctCount += count;
                score += ctCount * 16;
            }
        }

        if(gtcCount == 0 && (gtCount == 0 || ctCount == 0)) {
            //don't have a GRAPHICS | TRANSFER or a COMPUTE | TRANSFER queue
            return 0;
        }

        return score;
    }

    uint32_t VulkanManager::calculateDeviceScore(const vk::PhysicalDeviceGroupProperties& deviceGroup) {
        uint32_t sum = 0;

        for(uint32_t i = 0; i < deviceGroup.physicalDeviceCount; i++) {
            sum += VulkanManager::calculateDeviceScore(deviceGroup.physicalDevices[i]);
        }

        return sum;
    }

    void VulkanManager::init(void) {
        VulkanManager::initSingleton(new VulkanManager());
    }

    void VulkanManager::deinit(void) {
        VulkanManager::deinitSingleton();
    }

    vk::Instance VulkanManager::getInstance(void) {
        return this->instance;
    }

    bool VulkanManager::hasLayer(const String& layer) {
        if(this->instanceLayers.size() == 0) {
            this->instanceLayers = vk::enumerateInstanceLayerProperties();
        }

        for(auto& prop: this->instanceLayers) {
            if(layer == prop.layerName) {
                return true;
            }
        }

        return false;
    }

    bool VulkanManager::hasExtension(const String& extension) {
        if(this->instanceExtensions.size() == 0) {
            this->instanceExtensions = vk::enumerateInstanceExtensionProperties();
        }

        for(auto& prop: this->instanceExtensions) {
            if(extension == prop.extensionName) {
                return true;
            }
        }

        return false;
    }

    Version getVersion(void) {
        return convertVersion(vk::enumerateInstanceVersion());
    }

    #ifdef _WIN32
    #include "platform/windows/VulkanManager.cpp"
    #elif defined(__linux__)
    #include "platform/linux/VulkanManager.cpp"
    #endif
}
