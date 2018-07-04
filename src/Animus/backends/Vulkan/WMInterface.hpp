#ifndef ANIMUS_VULKAN_SWAPCHAIN
#define ANIMUS_VULKAN_SWAPCHAIN

#include "WMInterface.hpp"

namespace Animus::Vulkan {
    class WMInterface {
        vk::Format surfaceFormat;
        vk::ColorSpaceKHR surfaceColorSpace;
        UnsafeVector<vk::PresentModeKHR> presentModes;
        Optional<vk::Swapchain> swapchain;
        uint32_t queueFamily;
        vk::SurfaceKHR surface;
        vk::DispatchLoaderDynamic dispatch;

        void createSurface(const NativeWindow& nativeWindow, const vk::DispatchLoaderDynamic& dispatch);

    public:
        WMInterface(const NativeWindow& nativeWindow);
        WMInterface(void) = default;
        ~WMInterface(void);

        bool isDeviceSupported(const vk::PhysicalDevice& physicalDevice, uint32_t queueFamily);

        void selectDevice(const vk::PhysicalDevice& physicalDevice, uint32_t queueFamily);
        void create(bool vsync, uint32_t images, const Vec2i& size);
        void preset(void);
    };
}
#endif
