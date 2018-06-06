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
    };
}
#endif
