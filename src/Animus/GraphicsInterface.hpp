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

        virtual void setBuffering(uint32_t count) = 0;
        virtual void enableVsync(bool enabled) = 0;
        virtual void present(void) = 0;
    };
}
#endif
