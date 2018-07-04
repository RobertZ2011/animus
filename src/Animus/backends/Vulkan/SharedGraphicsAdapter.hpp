#ifndef ANIMUS_SHARED_GRAPHICS_ADAPTER
#define ANIMUS_SHARED_GRAPHICS_ADAPTER

#include "WMInterface.hpp"
#include "SharedDevice.hpp"

namespace Animus::Vulkan {
    class SharedGraphicsAdapter : public GraphicsInterface_ {
        WMInterface *wmInterface;
        SharedDevice *sharedDevice;
        bool vsync;
        Vec2i size;
        uint32_t images;

    public:
        SharedGraphicsAdapter(WMInterface * wmInterface, SharedDevice *sharedDevice);
        ~SharedGraphicsAdapter(void);

        void resize(const Vec2i& size) override;
        void enableVsync(bool enable) override;
        void setBuffering(uint32_t images) override;
        void setDisplayProperties(const Vec2i& size, bool vsync, uint32_t buffering) override;
        void present(void) override;
    };
}
#endif
