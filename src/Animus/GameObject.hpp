#ifndef ANIMUS_GAME_OBJECT
#define ANIMUS_GAME_OBJECT

#include "types.hpp"

namespace Animus {
    class GameObject {
    protected:
        Vec3f position;
        Vec3f scale;
        Quat rotation;
    };
}

#endif
