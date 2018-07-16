#include "Instance.hpp"
#include "vulkan.hpp"
#include "Error.hpp"
#include "PhysicalDevice.hpp"
#include "../../Log.hpp"

namespace Animus::Vulkan {
    Instance::Instance(void) {
        vk::ApplicationInfo appInfo(nullptr, 1, "Animus", convertVersion(::Animus::getVersion()), VK_API_VERSION_1_0);
        vk::InstanceCreateInfo createInfo;
        UnsafeVector<const char*> layers;
        UnsafeVector<const char*> extensions = this->getInstanceExtensions();

        #ifdef DEBUG
            layers.push_back("VK_LAYER_LUNARG_standard_validation");
        #endif

        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = &extensions[0];
        createInfo.enabledLayerCount = layers.size();
        createInfo.ppEnabledLayerNames = &layers[0];

        this->instance = vk::createInstance(createInfo);
        Log::getSingleton().log("Created Vulkan instance, version: %", convertVkVersion(vk::enumerateInstanceVersion()));

        this->dispatch = vk::DispatchLoaderDynamic(this->instance);
    }

    Instance::~Instance(void) {
        if(this->instance) {
            this->instance.destroy();
        }
    }

    bool Instance::hasExtension(const String& name) {
        UnsafeVector<vk::ExtensionProperties> extensions = vk::enumerateInstanceExtensionProperties();

        for(auto& extension: extensions) {
            if(extension.extensionName == name) {
                return true;
            }
        }

        return false;
    }

    vk::Instance Instance::getInstance(void) {
        return this->instance;
    }

    vk::DispatchLoaderDynamic& Instance::getDispatch(void) {
        return this->dispatch;
    }

    bool Instance::supportsMultiGPU(void) {
        //Version version = convertVkVersion(vk::enumerateInstanceVersion());

        ANIMUS_TODO("Remove this later");
        return false;
        /*if(version >= Version(1, 1, 0)) {
            return true;
        }
        else {
            return this->hasExtension("VK_KHR_device_group"); //VK_KHR_device_group requires VK_KHR_device_group_creation
        }*/
    }

    UnsafeVector<PhysicalDevice> Instance::enumerateDevices(void) {
        UnsafeVector<PhysicalDevice> devices;

        if(this->supportsMultiGPU()) {
            //every physical device must be in at least one device group
            auto groups = this->instance.enumeratePhysicalDeviceGroups(this->dispatch);
            for(auto& group: groups) {
                devices.push_back(PhysicalDevice(*this, group));
            }
        }
        else {
            auto physicalDevices = this->instance.enumeratePhysicalDevices(this->dispatch);
            for(auto& device: physicalDevices) {
                devices.push_back(PhysicalDevice(*this, device));
            }
        }

        return devices;
    }
}

#include "platform/Instance.cpp"