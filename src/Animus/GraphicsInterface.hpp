#ifndef ANIMUS_GRAPHICS_INTERFACE
#define ANIMUS_GRAPHICS_INTERFACE

#include "types.hpp"
#include "version.hpp"

namespace Animus {
    class GraphicsInterface_;
    typedef Pointer<GraphicsInterface_> GraphicsInterface;

    class GraphicsInterface_ {
    public:
        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;

        virtual void resize(const Vec2i& size) = 0;
        virtual void enableVsync(bool enable) = 0;
        virtual void setBuffering(uint32_t images) = 0;
        virtual void setDisplayProperties(const Vec2i& size, bool vsync, uint32_t buffering) = 0;
        virtual void present(void) = 0;
    };
}
#endif
