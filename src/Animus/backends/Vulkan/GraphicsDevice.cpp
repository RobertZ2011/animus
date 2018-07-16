#include "GraphicsDevice.hpp"
#include "../../Log.hpp"
#include "../../types/Queue.hpp"

#include <alloca.h>

namespace Animus::Vulkan {
    GraphicsDevice::GraphicsDevice(Instance& instance, PhysicalDevice& device, const Window& window, bool vysnc, uint32_t buffers) : 
        Device(instance, device) {
        this->init(vk::QueueFlagBits::eGraphics);
        this->swapchain = new Swapchain(instance, *this, window, vysnc, buffers);
    }

    GraphicsDevice::~GraphicsDevice(void) {
        if(this->swapchain) {
            delete swapchain;
        }
    }

    String GraphicsDevice::getName(void) {
        return "Vulkan Graphics Device";
    }

    Version GraphicsDevice::getVersion(void) {
        return Version(0, 0, 1);
    }

    void GraphicsDevice::setWindow(const Pointer<Window_>& window) {
        this->swapchain->recreate(window);
    }

    void GraphicsDevice::resize(const Vec2i& size) {

    }

    void GraphicsDevice::enableVsync(bool enabled) {

    }

    void GraphicsDevice::setBuffering(uint32_t buffers) {

    }

    void GraphicsDevice::setDisplayProperties(const Vec2i& size, bool vsync, uint32_t buffering) {

    }
    
    void GraphicsDevice::present(void) {
        
    }

    bool GraphicsDevice::supportsSurface(vk::SurfaceKHR surface) {
        if(!this->physicalDevice.isMulti()) {
            return this->physicalDevice.getDevice().getSurfaceSupportKHR(this->workFamily, surface, this->instance.getDispatch());
        }
        else {
            ANIMUS_TODO("implement this");
            return false;
        }
    }

    VertexStage GraphicsDevice::createVertexStage(const Stream& stream) {
        return ::Animus::VertexStage(nullptr);
    }

    GeometryStage GraphicsDevice::createGeometryStage(const Stream& stream) {
        return ::Animus::GeometryStage(nullptr);
    }

    FragmentStage GraphicsDevice::createFragmentStage(const Stream& stream) {
        return ::Animus::FragmentStage(nullptr);
    }

    UnsafeVector<const char*> GraphicsDevice::getDeviceExtensions(void) {
        UnsafeVector<const char*> extensions = {"VK_KHR_swapchain"};
        return extensions;
    }
}