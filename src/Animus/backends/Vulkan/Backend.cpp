#include "Backend.hpp"
#include "vulkan.hpp"
#include "../../version.hpp"
#include "../../Log.hpp"
#include "Error.hpp"
#include "PhysicalDevice.hpp"
#include "GraphicsDevice.hpp"

namespace Animus::Vulkan {
    String Backend::getName(void) {
        return "Vulkan Graphics/Compute";
    }

    Version Backend::getVersion(void) {
        return Version(1, 0, 0);
    }

    void Backend::init(void) {
        auto vulkanObj = SharedObject_::create(this->locateVulkan());

        //These are the only functions we need to load, the dynamic dispatch from vulkan.hpp will handle the rest
        vkGetInstanceProcAddr = vulkanObj->loadFunction<PFN_vkVoidFunction(VkInstance, const char*)>("vkGetInstanceProcAddr");
        vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance");
        vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceLayerProperties");
        vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
        vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceVersion");

        this->instance = new Instance();

        vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) vkGetInstanceProcAddr(this->instance->getInstance(), "vkGetDeviceProcAddr");
    }

    void Backend::deinit(void) {
        delete this->instance;
    }

    const UnsafeVector<GraphicsInterfaceInfo>& Backend::getGraphicsInterfaces(void) {
        return this->graphicsInfo;
    }

    const UnsafeVector<ComputeInterfaceInfo>& Backend::getComputeInterfaces(void) {
        return this->computeInfo;
    }

    GraphicsInterface Backend::createGraphicsInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) {
        PhysicalDevice device = this->selectDevice();
        GraphicsDevice *graphics = new GraphicsDevice(*this->instance, device, window, true, 2);
        this->graphics = GraphicsInterface((GraphicsInterface_*) graphics);

        return this->graphics;
    }

    ComputeInterface Backend::createComputeInterface(const String& name, Optional<Version> version) {
        return this->compute;
    }

    PhysicalDevice Backend::selectDevice(void) {
        auto devices = this->instance->enumerateDevices();

        std::sort(devices.begin(), devices.end(), [](PhysicalDevice& a, PhysicalDevice& b) {
            return a.calculateScore() > b.calculateScore();
        });

        Log::getSingleton().log("Found % devices", devices.size());
        for(auto& device: devices) {
            Log::getSingleton().log("\t% %", device.getName(), device.calculateScore());
        }

        return devices[0];
    }
}

#include "platform/Backend.cpp"