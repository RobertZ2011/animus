#include "SharedObject.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    SharedObject_::SharedObject_(const FilePath& path) {
        this->so = SDL_LoadObject(path.c_str());

        if(!this->so) {
            throw SharedObject_::CannotOpen(path);
        }
    }

    SharedObject_::~SharedObject_(void) {
        if(this->so) {
            SDL_UnloadObject(this->so);
        }
    }

    void *SharedObject_::loadSymbol(const String& name) {
        void *func = SDL_LoadFunction(this->so, name.c_str());

        if(!func) {
            throw SharedObject_::NoFunction(name);
        }

        return func;
    }

    SharedObject SharedObject_::create(const FilePath& path) {
        auto so = SharedObject(new SharedObject_(path));
        so->self = so;
        return so;
    }
}
