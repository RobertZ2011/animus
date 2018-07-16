#include "Swapchain.hpp"
#include "GraphicsDevice.hpp"
#include "Error.hpp"
#include "Instance.hpp"
#include "../../Log.hpp"

namespace Animus::Vulkan {
    Swapchain::Swapchain(Instance& instance, GraphicsDevice& device, const Window& window, bool vsync, uint32_t buffers) : 
        instance(instance),
        device(device) {
        this->size = window->getSize();
        this->buffers = buffers;
        this->vsync = vsync;
        this->surface = surface;

        this->recreate(window);
    }

    Swapchain::~Swapchain() {
        if(this->swapchain) {
            this->device.getDevice().destroySwapchainKHR(this->swapchain, nullptr, this->device.getDispatch());
        }

        if(this->surface) {
            this->instance.getInstance().destroySurfaceKHR(this->surface, nullptr, this->instance.getDispatch());
        }
    }

    void Swapchain::recreate(const Window& window) {
        this->createSurface(window);

        if(!this->device.supportsSurface(this->surface)) {
            ANIMUS_TODO("Throw exception");
        }

        auto capabilities = this->getCapabilities();

        if(!(capabilities.supportedUsageFlags & vk::ImageUsageFlagBits::eTransferDst)) {
            Log::getSingleton().warnStr("Surface doesn't support TransferDst");
        }

        if(!(capabilities.supportedUsageFlags & vk::ImageUsageFlagBits::eTransferSrc)) {
            Log::getSingleton().warnStr("Surface doesn't support TransferSrc");
        }

        if(!(capabilities.supportedUsageFlags & vk::ImageUsageFlagBits::eSampled)) {
            Log::getSingleton().warnStr("Surface doesn't support Sampled");
        }

        this->size = window->getSize();
        this->set(this->size, this->vsync, this->buffers);
    }

    void Swapchain::set(const Vec2i& size, bool vsync, uint32_t buffers) {
        vk::SwapchainCreateInfoKHR info;

        info.minImageCount = buffers;
        info.surface = this->surface;
        info.imageFormat = vk::Format::eB8G8R8A8Unorm;
        info.imageExtent = vk::Extent2D(size.x, size.y);
        info.imageArrayLayers = 1;

        //allow the swapchain to be transferred and sampled
        info.imageUsage = vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eTransferSrc;
        info.imageSharingMode = vk::SharingMode::eExclusive;
        info.presentMode = (vsync) ? vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eImmediate;
        info.clipped = false;
        info.oldSwapchain = this->swapchain;

        this->swapchain = this->device.getDevice().createSwapchainKHR(info, nullptr, this->device.getDispatch());
        Log::getSingleton().logStr("Created swapchain");
    }

    void Swapchain::resize(const Vec2i& size) {
        this->size = size;
        this->set(this->size, this->vsync, this->buffers);
    }

    void Swapchain::enableVsync(bool enable) {
        this->vsync = enable;
        this->set(this->size, this->vsync, this->buffers);
    }

    void Swapchain::setBuffering(uint32_t buffers) {
        this->buffers = buffers;
        this->set(this->size, this->vsync, this->buffers);
    }

    vk::SurfaceCapabilitiesKHR Swapchain::getCapabilities(void) {
        if(!this->device.isMulti()) {
            //For some reason, this will crash with the device dispatch because it doesn't load the function, using instance for now
            return this->device.getPhysicalDevice().getDevice().getSurfaceCapabilitiesKHR(this->surface, this->instance.getDispatch());
        }
        else {
            ANIMUS_TODO("implement this");
            return vk::SurfaceCapabilitiesKHR();
        }
    }
}

#include "platform/Swapchain.cpp"