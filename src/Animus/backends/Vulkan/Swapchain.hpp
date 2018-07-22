#ifndef ANIMUS_VULKAN_SWAPCHAIN
#define ANIMUS_VULKAN_SWAPCHAIN

#include "../../Window.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class GraphicsDevice_;
    class Instance_;

    class Swapchain_ : public WindowProxy_ {
        Vec2i size;
        bool vsync;
        uint32_t buffers;
        vk::SurfaceKHR surface;
        vk::SwapchainKHR swapchain;
        Pointer<Instance_> instance;
        Pointer<GraphicsDevice_> device;

    public:
        ~Swapchain_(void);

        void recreate(const Window& window);
        void resize(const Vec2i& size);
        void enableVsync(bool enabled);
        void setBuffering(uint32_t buffers);
        void setDisplayParams(const Vec2i& size, bool vsync, uint32_t buffers);

        static Pointer<Swapchain_> create(const Pointer<Instance_>& instace, const Pointer<GraphicsDevice_>& device, const Window& window, bool vsync, uint32_t buffers);

    private:
        Swapchain_(const Pointer<Instance_>& instance, const Pointer<GraphicsDevice_>& device, const Window& window, bool vsync, uint32_t buffers);
        void createSurface(const Window& window);
        vk::SurfaceCapabilitiesKHR getCapabilities(void);
    };
    typedef Pointer<Swapchain_> Swapchain;
}
#endif