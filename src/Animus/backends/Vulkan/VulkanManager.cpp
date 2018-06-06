#include "VulkanManager.hpp"

namespace Animus {
namespace Vulkan {
    VulkanManager::VulkanManager(void) {
        #ifdef DEBUG
            const char *layers[] = {
                "VK_LAYER_LUNARG_standard_validation"
            };
            int layerCount = 1;
        #else
            const char **layers = nullptr;
            int layerCount = 0;
        #endif

        const char *extensions[] = {
            "VK_KHR_surface",
            #ifdef _WIN32
                "VK_KHR_win32_surface",
            #elif defined(__linux__)
                "VK_KHR_xlib_surface",
                "VK_KHR_wayland_surface",
            #endif
        };
        int extensionCount = 3;

        //open vulkan library and load basic functions
        #ifdef _WIN32
            this->so = SharedObject_::cretae("vulkan-1.dll");
        #elif defined(__linux__)
            this->so = SharedObject_::create("libvulkan.so");
        #endif
        vkGetInstanceProcAddr = this->so->loadFunction<PFN_vkVoidFunction(VkInstance, const char*)>("vkGetInstanceProcAddr");
        this->loadBaseFunctions();

        vk::InstanceCreateInfo info;
        vk::ApplicationInfo appInfo;

        info.enabledLayerCount = layerCount;
        info.ppEnabledLayerNames = layers;

        info.enabledExtensionCount = extensionCount;
        info.ppEnabledExtensionNames = extensions;

        this->instance = vk::createInstance(info);
        //this->instanceDispatch = vk::DispatchLoaderDynamic(this->instance);
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
        if(this->extensionLayers.size() == 0) {
            this->extensionLayers = vk::EnumerateInstanceExtensionProperties();
        }

        for(auto& prop: this->instanceExtensions) {
            if(extension == prop.extensionName) {
                return true;
            }
        }

        return false;
    }
}
}
