#include "GraphicsDevice.hpp"
#include "../../Log.hpp"
#include "../../types/Queue.hpp"

#include <alloca.h>

namespace Animus::Vulkan {
    GraphicsDevice_::GraphicsDevice_(const Instance& instance, const PhysicalDevice& device) : 
        Device_(instance, device) {
        this->init(vk::QueueFlagBits::eGraphics);
    }

    GraphicsDevice_::~GraphicsDevice_(void) {
    }

    String GraphicsDevice_::getName(void) {
        return "Vulkan Graphics Device";
    }

    Version GraphicsDevice_::getVersion(void) {
        return Version(0, 0, 1);
    }

    void GraphicsDevice_::attachTarget(const RenderTarget& target) {
        if(target->getRenderTargetType() == RenderTargetProxy_::Type::Window) {
            //by default enable vsync and double buffering
            auto proxy = staticCast<RenderTargetProxy_>(Swapchain_::create(this->instance, staticCast<GraphicsDevice_>(this->self.lock()), staticCast<Window_>(target), true, 2));
            this->targets.push_back(proxy);
            target->registerProxy(proxy);
        }
    }

    void GraphicsDevice_::removeTarget(const RenderTarget& target) {
        this->targets.erase(std::find(this->targets.begin(), this->targets.end(), target->getRenderTargetProxy()));
    }
    
    void GraphicsDevice_::render(void) {
        
    }

    bool GraphicsDevice_::supportsSurface(vk::SurfaceKHR surface) {
        if(!this->physicalDevice->isMulti()) {
            return this->physicalDevice->getDevice().getSurfaceSupportKHR(this->workFamily, surface, this->instance->getDispatch());
        }
        else {
            ANIMUS_TODO("implement this");
            return false;
        }
    }

    VertexStage GraphicsDevice_::createVertexStage(const Stream& stream) {
        return ::Animus::VertexStage(nullptr);
    }

    GeometryStage GraphicsDevice_::createGeometryStage(const Stream& stream) {
        return ::Animus::GeometryStage(nullptr);
    }

    FragmentStage GraphicsDevice_::createFragmentStage(const Stream& stream) {
        return ::Animus::FragmentStage(nullptr);
    }

    UnsafeVector<const char*> GraphicsDevice_::getDeviceExtensions(void) {
        UnsafeVector<const char*> extensions = {"VK_KHR_swapchain"};
        return extensions;
    }

    Pointer<GraphicsDevice_> GraphicsDevice_::create(const Instance& instance, const PhysicalDevice& device) {
        auto ptr = Pointer<GraphicsDevice_>(new GraphicsDevice_(instance, device));
        ptr->self = ptr;
        return ptr;
    }
}