#include "Backend.hpp"
#include "vulkan.hpp"
#include "../../version.hpp"
#include "../../Log.hpp"
#include "Error.hpp"

namespace Animus::Vulkan {
    String Backend::getName(void) {
        return "Vulkan Graphics/Compute";
    }

    Version Backend::getVersion(void) {
        return Version(1, 0, 0);
    }

    void Backend::init(const Pointer<Window_>& window) {
        auto vulkanObj = SharedObject_::create(this->locateVulkan());
        vk::ApplicationInfo appInfo(nullptr, 1, "Animus", convertVersion(::Animus::getVersion()), VK_API_VERSION_1_0);
        vk::InstanceCreateInfo createInfo;
        UnsafeVector<const char*> layers;
        UnsafeVector<const char*> extensions = this->getInstanceExtensions();

        //These are the only functions we need to load, the dynamic dispatch from vulkan.hpp will handle the rest
        vkGetInstanceProcAddr = vulkanObj->loadFunction<PFN_vkVoidFunction(VkInstance, const char*)>("vkGetInstanceProcAddr");
        vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
        vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties");
        vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties");
        vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion");

        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = &extensions[0];
        createInfo.enabledLayerCount = layers.size();
        createInfo.ppEnabledLayerNames = &layers[0];

        this->instance = vk::createInstance(createInfo);
        Log::getSingleton().log("Created Vulkan instance, version: %", convertVkVersion(vk::enumerateInstanceVersion()));

        this->dispatch = vk::DispatchLoaderDynamic(this->instance);
        this->createSurface(window);
    }

    void Backend::deinit(void) {
        if(this->instance) {
            this->instance.destroy();
        }
    }

    const UnsafeVector<GraphicsInterfaceInfo>& Backend::getGraphicsInterfaces(void) {
        return this->graphicsInfo;
    }

    const UnsafeVector<ComputeInterfaceInfo>& Backend::getComputeInterfaces(void) {
        return this->computeInfo;
    }

    GraphicsInterface Backend::createGraphicsInterface(const String& name, Optional<Version> version) {
        return Pointer<GraphicsInterface_>(nullptr);
    }

    ComputeInterface Backend::createComputeInterface(const String& name, Optional<Version> version) {
        return Pointer<ComputeInterface_>(nullptr);
    }
}

#include "platform/Backend.cpp"