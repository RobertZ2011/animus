#ifndef ANIMUS_VULKAN_SWAPCHAIN
#define ANIMUS_VULKAN_SWAPCHAIN

namespace Animus::Vulkan {
    class Swapchain {
        vk::Format surfaceFormat;
        vk::ColorSpaceKHR surfaceColorSpace;
        UnsafeVector<vk::PresentModeKHR> presentModes;
        Optional<vk::Swapchain> swapchain;
        uint32_t queueFamily;

    public:
        Swapchain(const vk::SurfaceKHR& surface, const vk::PhysicalDevice& physicalDevice, uint32_t queueFamily);
        ~Swapchain(void);

        void create(bool vsync, uint32_t images, const Vec2i& size, bool threeD);
        void preset(void);
    };
}
#endif
