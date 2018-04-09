#ifndef ANIMU_WINDOW
#define ANIMUS_WINDOW

#include "types.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    typedef Pointer<Window_> Window;
    class Window_ {
    private:
        SDL_Window *window;

        Window_(const Vec2i& size, const String& title);

    public:
        ~Window_();

        String getTitle(void);
        void setTitle(const String& title);

        static Window create(const Vec2i& size, const String& tittle);
    };
}
#endif
