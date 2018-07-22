#ifndef ANIMUS_TEXTURE
#define ANIMUS_TEXTURE

#include "../types/types.hpp"

namespace Animus {
    class Texture_ {
        virtual ~Texture_(void) = default;
    };
    typedef Pointer<Texture_> Texture;
}

#endif