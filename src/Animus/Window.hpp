#ifndef ANIMUS_WINDOW
#define ANIMUS_WINDOW

#include "types.hpp"
#include "Vector.hpp"
#include "GraphicsInterface.hpp"
#include "ComputeInterface.hpp"
#include "Backend.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    class Window_;
    typedef Pointer<Window_> Window;

    class Window_ {
    private:
        REQUIRES_SDL
        SDL_Window *window;
        WeakPtr<Window_> self;

        Window_(const Vec2i& size, const String& title);

    public:
        ~Window_();

        String getTitle(void);
        void setTitle(const String& title);

        REQUIRES_SDL
        void *getWMPointer(void);

        static Window create(const Vec2i& size, const String& title);
    };
}
#endif
