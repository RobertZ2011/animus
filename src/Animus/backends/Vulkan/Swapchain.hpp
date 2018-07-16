#ifndef ANIMUS_VULKAN_SWAPCHAIN
#define ANIMUS_VULKAN_SWAPCHAIN

#include "../../Window.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class GraphicsDevice;
    class Instance;

    class Swapchain {
        Vec2i size;
        bool vsync;
        uint32_t buffers;
        vk::SurfaceKHR surface;
        vk::SwapchainKHR swapchain;
        Instance& instance;
        GraphicsDevice& device;

    public:
        Swapchain(Instance& instance, GraphicsDevice& device, const Window& window, bool vsync, uint32_t buffers);
        ~Swapchain(void);

        void recreate(const Window& window);
        void resize(const Vec2i& size);
        void enableVsync(bool enabled);
        void setBuffering(uint32_t buffers);

    private:
        void set(const Vec2i& size, bool vsync, uint32_t buffers);
        void createSurface(const Window& window);
        vk::SurfaceCapabilitiesKHR getCapabilities(void);
    };
}
#endif