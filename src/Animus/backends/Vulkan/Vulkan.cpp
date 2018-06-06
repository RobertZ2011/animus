#include "Vulkan.hpp"
#include "VulkanManager.hpp"
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
        VulkanManager::init();
    }

    void Backend::deinit(void) {
        VulkanManager::deinit();
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
