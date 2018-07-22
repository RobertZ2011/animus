#ifndef ANIMUS_BACKEND_VULKAN
#define ANIMUS_BACKEND_VULKAN

#include "../../Backend.hpp"
#include "../../FilePath.hpp"
#include "../../SharedObject.hpp"
#include "../../Window.hpp"
#include "../../macros/debug.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

#include "Instance.hpp"
#include "PhysicalDevice.hpp"

namespace Animus::Vulkan {
    class Backend : public ::Animus::Backend {
        UnsafeVector<GraphicsInterfaceInfo> graphicsInfo = { GraphicsInterfaceInfo("Vulkan", Version(1, 0, 0)) };
        UnsafeVector<ComputeInterfaceInfo> computeInfo = { ComputeInterfaceInfo("Vulkan", Version(1, 0, 0)) };

        Instance instance;
        GraphicsInterface graphics;
        ComputeInterface compute;
    public:
        Backend(void) = default;
        ~Backend(void) = default;

        String getName(void) override;
        Version getVersion(void) override;

        void init(void) override;
        void deinit(void) override;

        const UnsafeVector<GraphicsInterfaceInfo>& getGraphicsInterfaces(void) override;
        const UnsafeVector<ComputeInterfaceInfo>& getComputeInterfaces(void) override;

        GraphicsInterface createGraphicsInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) override;
        ComputeInterface createComputeInterface(const String& name, Optional<Version> version) override;

    private:
        ANIMUS_REQUIRES_STD
        PhysicalDevice selectDevice(void);
        FilePath locateVulkan(void);
    };
}
#endif