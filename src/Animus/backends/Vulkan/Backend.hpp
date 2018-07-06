#ifndef ANIMUS_BACKEND_VULKAN
#define ANIMUS_BACKEND_VULKAN

#include "../../Backend.hpp"
#include "../../FilePath.hpp"
#include "../../SharedObject.hpp"
#include "../../Window.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class Backend : public ::Animus::Backend {
        UnsafeVector<GraphicsInterfaceInfo> graphicsInfo = { GraphicsInterfaceInfo("Vulkan", Version(1, 0, 0)) };
        UnsafeVector<ComputeInterfaceInfo> computeInfo = { ComputeInterfaceInfo("Vulkan", Version(1, 0, 0)) };

        vk::Instance instance;
        vk::SurfaceKHR surface;
        vk::DispatchLoaderDynamic dispatch;

    public:
        Backend(void) = default;
        ~Backend(void) = default;

        String getName(void) override;
        Version getVersion(void) override;

        void init(const Pointer<Window_>& window) override;
        void deinit(void) override;

        const UnsafeVector<GraphicsInterfaceInfo>& getGraphicsInterfaces(void) override;
        const UnsafeVector<ComputeInterfaceInfo>& getComputeInterfaces(void) override;

        GraphicsInterface createGraphicsInterface(const String& name, Optional<Version> version = Optional<Version>()) override;
        ComputeInterface createComputeInterface(const String& name, Optional<Version> version = Optional<Version>()) override;

    private:
        FilePath locateVulkan(void);
        UnsafeVector<const char*> getInstanceExtensions(void);
        bool hasExtension(const String& name);
        void createSurface(const Pointer<Window_>& window);
    };
}
#endif