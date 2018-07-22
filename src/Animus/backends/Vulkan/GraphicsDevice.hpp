#ifndef ANIMUS_VULKAN_GRAPHICS_DEVICE
#define ANIMUS_VULKAN_GRAPHICS_DEVICE

#include "Device.hpp"
#include "Swapchain.hpp"
#include "Instance.hpp"

#include "../../GraphicsInterface.hpp"
#include "../../macros/debug.hpp"

namespace Animus::Vulkan {
    class GraphicsDevice_ : public Device_, public GraphicsInterface_ {
        UnsafeVector<RenderTargetProxy> targets;

    public:
        virtual ~GraphicsDevice_(void);

        String getName(void) override;
        Version getVersion(void) override;

        void attachTarget(const RenderTarget& target) override;
        ANIMUS_REQUIRES_STD
        void removeTarget(const RenderTarget& target) override;
        void render(void) override;

        bool supportsSurface(vk::SurfaceKHR surface);

        VertexStage createVertexStage(const Stream& stream);
        GeometryStage createGeometryStage(const Stream& stream);
        FragmentStage createFragmentStage(const Stream& stream);

        static Pointer<GraphicsDevice_> create(const Instance& instance, const PhysicalDevice& device);

    protected:
        //This will come in handy when we create shared devices
        GraphicsDevice_(void) = default;
        UnsafeVector<const char*> getDeviceExtensions(void) override;
        ANIMUS_REQUIRES_STD
        GraphicsDevice_(const Instance& instance, const PhysicalDevice& device);
    };

    typedef Pointer<GraphicsDevice_> GraphicsDevice;
}
#endif