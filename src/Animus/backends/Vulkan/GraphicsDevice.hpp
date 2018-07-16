#ifndef ANIMUS_VULKAN_GRAPHICS_DEVICE
#define ANIMUS_VULKAN_GRAPHICS_DEVICE

#include "Device.hpp"
#include "Swapchain.hpp"
#include "Instance.hpp"

#include "../../GraphicsInterface.hpp"
#include "../../Object.hpp"

namespace Animus::Vulkan {
    class GraphicsDevice : public Device, public GraphicsInterface_ {
        Swapchain *swapchain;

    public:
        ANIMUS_REQUIRES_STD
        GraphicsDevice(Instance& instance, PhysicalDevice& device, const Window& window, bool vysnc, uint32_t buffers);
        virtual ~GraphicsDevice(void);

        String getName(void) override;
        Version getVersion(void) override;

        void setWindow(const Pointer<Window_>& window) override;
        void resize(const Vec2i& size) override;
        void enableVsync(bool enabled) override;
        void setBuffering(uint32_t buffers) override;
        void setDisplayProperties(const Vec2i& size, bool vsync, uint32_t buffering) override;
        void present(void) override;

        bool supportsSurface(vk::SurfaceKHR surface);

        VertexStage createVertexStage(const Stream& stream);
        GeometryStage createGeometryStage(const Stream& stream);
        FragmentStage createFragmentStage(const Stream& stream);

    protected:
        //This will come in handy when we create shared devices
        GraphicsDevice(void) = default;
        UnsafeVector<const char*> getDeviceExtensions(void) override;
    };
}
#endif