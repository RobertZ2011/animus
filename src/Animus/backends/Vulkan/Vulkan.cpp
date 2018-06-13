#include "Vulkan.hpp"
#include "VulkanManager.hpp"
#include "../../Log.hpp"

Animus::Backend *create_backend(void) {
    return new Animus::Vulkan::Backend();
}

void destroy_backend(Animus::Backend *backend) {
    delete backend;
}

namespace Animus::Vulkan {
    String Backend::getName(void) {
        return "Vulkan";
    }

    Version Backend::getVersion(void) {
        return Version(0, 0, 1);
    }

    void Backend::init(const Window& window) {
        Log::getSingleton().logStr("Vulkan Init");
        VulkanManager::init(window->getNativeWindow());
    }

    void Backend::deinit(void) {
        Log::getSingleton().logStr("Vulkan deinit");
        VulkanManager::deinit();
    }

    const UnsafeVector<GraphicsInterfaceInfo>& Backend::getGraphicsInterfaces(void) {
        return this->graphicsInfo;
    }

    const UnsafeVector<ComputeInterfaceInfo>& Backend::getComputeInterfaces(void) {
        return this->computeInfo;
    }

    GraphicsInterface Backend::createGraphicsInterface(const String& name, Optional<Version> version) {
        return GraphicsInterface(nullptr);
    }

    ComputeInterface Backend::createComputeInterface(const String& name, Optional<Version> version) {
        return ComputeInterface(nullptr);
    }
}
