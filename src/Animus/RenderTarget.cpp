#include "RenderTarget.hpp"

namespace Animus {
    void RenderTarget_::registerProxy(const RenderTargetProxy& proxy) {
        this->renderTargetProxy = proxy;
    }

    void RenderTarget_::unregisterProxy(void) {
        this->renderTargetProxy = nullptr;
    }

    RenderTargetProxy RenderTarget_::getRenderTargetProxy(void) {
        return this->renderTargetProxy;
    }

    const char *NoRenderProxy::what(void) const noexcept {
        return "Missing render proxy";
    }

}