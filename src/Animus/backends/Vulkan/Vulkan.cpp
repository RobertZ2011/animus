#include "Vulkan.hpp"
#include "Loader.hpp"
#include "../../Log.hpp"

Animus::Backend *create_backend(void) {
    return new Animus::Vulkan::Backend();
}

void destroy_backend(Animus::Backend *backend) {
    delete backend;
}

namespace Animus{
namespace Vulkan {
    String Backend::getName(void) {
        return "Vulkan";
    }

    Version Backend::getVersion(void) {
        return Version(0, 0, 1);
    }

    void Backend::init(void) {
        VkResult res;
        VkInstance instance;
        VkInstanceCreateInfo instanceInfo;
        uint32_t version;

        Loader::init();
        Loader::getSingleton().loadBaseFunctions();

        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pNext = nullptr;
        instanceInfo.flags = 0;
        instanceInfo.pApplicationInfo = nullptr;
        instanceInfo.enabledLayerCount = 0;
        instanceInfo.ppEnabledLayerNames = nullptr;
        instanceInfo.enabledExtensionCount = 0;
        instanceInfo.ppEnabledExtensionNames = nullptr;

        res = vkCreateInstance(&instanceInfo, nullptr, &instance);
        if(res != VK_SUCCESS) {
            Log::getSingleton().fatalStr("Failed to create instance");
        }

        vkEnumerateInstanceVersion(&version);
        Log::getSingleton().log("Got version %", convertVersion(version));
    }

    void Backend::deinit(void) {
        Loader::deinit();
    }

    const UnsafeVector<GraphicsInterfaceInfo>& Backend::getGraphicsInterfaces(void) {
        return this->graphicsInfo;
    }

    const UnsafeVector<ComputeInterfaceInfo>& Backend::getComputeInterfaces(void) {
        return this->computeInfo;
    }

    GraphicsInterface Backend::createGraphicsInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) {
        return GraphicsInterface(nullptr);
    }

    ComputeInterface Backend::createComputeInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) {
        return ComputeInterface(nullptr);
    }

    Version convertVersion(uint32_t version) {
        uint32_t major = (version >> 22) & 0x3FF;
        uint32_t minor = (version >> 12) & 0x3FF;
        uint32_t patch = version & 0xFFF;

        return Version(major, minor, patch);
    }
}
}
