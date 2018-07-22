#include "Swapchain.hpp"
#include "GraphicsDevice.hpp"
#include "Error.hpp"
#include "Instance.hpp"
#include "../../Log.hpp"

namespace Animus::Vulkan {
    Swapchain_::Swapchain_(const Pointer<Instance_>& instance, const Pointer<GraphicsDevice_>& device, const Window& window, bool vsync, uint32_t buffers) : 
        instance(instance),
        device(device) {
        this->size = window->getSize();
        this->buffers = buffers;
        this->vsync = vsync;
        this->surface = surface;

        this->recreate(window);
    }

    Swapchain_::~Swapchain_() {
        if(this->swapchain) {
            this->device->getDevice().destroySwapchainKHR(this->swapchain, nullptr, this->device->getDispatch());
        }

        if(this->surface) {
            this->instance->getInstance().destroySurfaceKHR(this->surface, nullptr, this->instance->getDispatch());
        }
    }

    void Swapchain_::recreate(const Window& window) {
        this->createSurface(window);

        if(!this->device->supportsSurface(this->surface)) {
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
        this->setDisplayParams(this->size, this->vsync, this->buffers);
    }

    void Swapchain_::setDisplayParams(const Vec2i& size, bool vsync, uint32_t buffers) {
        vk::SwapchainCreateInfoKHR info;
        Log::getSingleton().logStr(this->device->getPhysicalDevice()->getName());
        auto presentModes = this->device->getPhysicalDevice()->getDevice().getSurfacePresentModesKHR(this->surface, this->device->getDispatch());
        auto formats = this->device->getPhysicalDevice()->getDevice().getSurfaceFormatsKHR(this->surface, this->device->getDispatch());
        //vk::Format selectedFormat;
        //vk::PresentModeKHR presentMode;

        info.minImageCount = buffers;
        info.surface = this->surface;
        info.imageFormat = vk::Format::eB8G8R8A8Unorm;
        info.imageExtent = vk::Extent2D(size.x, size.y);
        info.imageArrayLayers = 1;

        //allow the Swapchain to be transferred and sampled
        info.imageUsage = vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eTransferSrc;
        info.imageSharingMode = vk::SharingMode::eExclusive;
        info.presentMode = (vsync) ? vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eImmediate;
        info.clipped = false;
        info.oldSwapchain = this->swapchain;

        this->swapchain = this->device->getDevice().createSwapchainKHR(info, nullptr, this->device->getDispatch());
        Log::getSingleton().logStr("Created Swapchain");
    }

    Pointer<Swapchain_> Swapchain_::create(const Pointer<Instance_>& instance, const Pointer<GraphicsDevice_>& device, const Window& window, bool vsync, uint32_t buffers) {
        return Pointer<Swapchain_>(new Swapchain_(instance, device, window, vsync, buffers));
    }

    void Swapchain_::resize(const Vec2i& size) {
        this->size = size;
        this->setDisplayParams(this->size, this->vsync, this->buffers);
    }

    void Swapchain_::enableVsync(bool enable) {
        this->vsync = enable;
        this->setDisplayParams(this->size, this->vsync, this->buffers);
    }

    void Swapchain_::setBuffering(uint32_t buffers) {
        this->buffers = buffers;
        this->setDisplayParams(this->size, this->vsync, this->buffers);
    }

    vk::SurfaceCapabilitiesKHR Swapchain_::getCapabilities(void) {
        if(!this->device->isMulti()) {
            //For some reason, this will crash with the device dispatch because it doesn't load the function, using instance for now
            return this->device->getPhysicalDevice()->getDevice().getSurfaceCapabilitiesKHR(this->surface, this->instance->getDispatch());
        }
        else {
            ANIMUS_TODO("implement this");
            return vk::SurfaceCapabilitiesKHR();
        }
    }
}

#include "platform/Swapchain.cpp"