#ifndef ANIMUS_GRAPHICS_INTERFACE
#define ANIMUS_GRAPHICS_INTERFACE

#include "types.hpp"
#include "version.hpp"

namespace Animus {
    class _GraphicsInterface;
    typedef Pointer<_GraphicsInterface> GraphicsInterface;

    class _GraphicsInterface {
    public:
        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;
    };
}
#endif
