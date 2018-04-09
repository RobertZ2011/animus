#include "Window.hpp"

namespace Animus {
    Window_::Window_(const Vec2i& size, const String& title) {
        this-> window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            size.x,
            size.y,
            0
        );
    }

    Window_::~Window_() {
        if(this->window) {
            SDL_DestroyWindow(this->window);
        }
    }
}
