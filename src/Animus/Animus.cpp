#include "Animus.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    void init(void) {
        SDL_Init(SDL_INIT_EVERYTHING);
        ThreadPool::init();
    }

    void deinit(void) {
        ThreadPool::deinit();
        SDL_Quit();
    }

    Version getVersion(void) {
        return Version(0, 0, 1);
    }
}
