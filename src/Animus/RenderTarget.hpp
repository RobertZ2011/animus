#ifndef ANIMUS_RENDER_TARGET
#define ANIMUS_RENDER_TARGET

#include "types/types.hpp"

namespace Animus {
    // This class solves a problem with the idea of render targets
    // Take a window, for example, it is a render target, but the actual code
    // required to render to that window will never be in that class because it
    // needs to be in the backend. For example, vulkan needs a swapchain to render
    // to a window. Likewise, that swapchain needs function to change
    // things like vsync, number of buffers, etc. What object should provide
    // that interface? Obviously the swapchain object needs to, but
    // we have to have access to the swapchain object to do it.
    // We can't access the swapchain object directly because it's
    // vulkan specific. It feels weird to give GraphicsInterface
    // those functions because there could be multiple windows
    // and multiple swapchains. The window object seems like a
    // natural place for it, but we cannot use inheritance to
    // get the desired behaivor. So, we give the window the required functions
    // and have it relay the function calls to a proxy object. In the case
    // of Window and vulkan, that proxy object will be the swapchain
    class RenderTargetProxy_ {
        public:
        enum class Type {
            Window,
            Texture,
        };

        virtual ~RenderTargetProxy_(void) = default;
        virtual Type getRenderTargetType(void) = 0;
    };
    typedef Pointer<RenderTargetProxy_> RenderTargetProxy;

    class RenderTarget_ {
        protected:
        RenderTargetProxy renderTargetProxy;

        public:
        virtual ~RenderTarget_(void) = default;

        virtual void registerProxy(const RenderTargetProxy& proxy);
        virtual void unregisterProxy(void);
        virtual RenderTargetProxy_::Type getRenderTargetType(void) = 0;
        virtual RenderTargetProxy getRenderTargetProxy(void);
    };
    typedef Pointer<RenderTarget_> RenderTarget;

    class NoRenderProxy : public Exception {
    public:
        NoRenderProxy(void) = default;
        ~NoRenderProxy(void) = default;

        const char *what(void) const noexcept override;
    };
}
#endif
