#ifndef ANIMUS_ENTITY
#define ANIMUS_ENTITY

#include "types/types.hpp"

namespace Animus {
    class Entity {
    protected:
        Vec3f position;
        Vec3f scale;
        Quat rotation;
    };
}

#endif
