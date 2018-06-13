#include "Swapchain.hpp"

namespace Animus::Vulkan {
    Swapchain::Swapchain(const vk::SurfaceKHR& surface, const vk::PhysicalDevice& physicalDevice, const vk::Device& device, uint32_t queueFamily) {
        auto formats = physicalDevice.getPhysicalDeviceSurfaceFormatsKHR(this->surface, nullptr, this->dispatch);
        this->presentModes = physicalDevice.getPhysicalDeviceSurfacePresentModesKHR(nullptr, this->dispatch);

        if(formats.size()) {
            Log::getSingleton().errorStr("Found no surface formats");
            throw RuntimeError("Found no surface formats");
        }

        //just use the first one
        this->surfaceFormat = formats[0].format;
        this->surfaceColorSpace = formats[0].colorSpace;

        this->queueFamily = queueFamily;
    }

    Swapchain::~Swapchain(void) {

    }

    void Swapchain::create(bool vsync, uint32_t images, const Vec2i& size, bool threeD) {
        vk::SwapchainCreateInfoKHR info;
        vk::PresentModeKHR presentMode;

        if(!vsync) {

        }

        info.surface = this->surface;
        info.minImageCount = images;
        info.imageFormat = this->surfaceFormat;
        info.imageColorSpace = this->surfaceColorSpace;
        info.imageExtent = vk::Extent2D(size.x, size.y);
        info.imageArrayLayers = 1;
        info.imageUsage = vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
        info.imageSharingMode = vk::SharingMode::eExclusive;
        info.queueFamilyIndexCount = 1;
        info.pQueueFamilyIndices = &this->queueFamily;
        info.preTransform = vk::SurfaceTransformFlagBitsKHR::eInherit;
        info.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eInherit;
        info.presentMode = ;
        info.clipped = true;
        if(this->swapchain.has_value()) {
            info.oldSwapchain = this->swapchain.value()
        }

        this->swapchain = device.createSwapchainKHR(info, nullptr, this->dispatch);
    }

    void Swapchain::present(void) {

    }
}
