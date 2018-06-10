#ifndef ANIMUS_VULKAN
#define ANIMUS_VULKAN

#include "../../Backend.hpp"

extern "C" Animus::Backend *create_backend(void);
extern "C" void destroy_backend(Animus::Backend *backend);

namespace Animus::Vulkan {
    class Backend : public ::Animus::Backend {
        UnsafeVector<GraphicsInterfaceInfo> graphicsInfo = {
            GraphicsInterfaceInfo("Vulkan", Version(1, 1, 0))
        };

        UnsafeVector<ComputeInterfaceInfo> computeInfo = {
            ComputeInterfaceInfo("Vulkan", Version(1, 1, 0))
        };

    public:
        Backend(void) = default;
        virtual ~Backend(void) = default;

        String getName(void) override;
        Version getVersion(void) override;

        void init(void) override;
        void deinit(void) override;

        const UnsafeVector<GraphicsInterfaceInfo>& getGraphicsInterfaces(void) override;
        const UnsafeVector<ComputeInterfaceInfo>& getComputeInterfaces(void) override;

        GraphicsInterface createGraphicsInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) override;
        ComputeInterface createComputeInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) override;
    };
}
#endif
