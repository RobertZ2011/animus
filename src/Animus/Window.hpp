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

        Window_(const Vec2i& size, const String& title, bool fullscreen);
        Window_(const String& title);

    public:
        enum class WMType {
            Windows,
            X11,
            Cocoa,
            Wayland
        };

        ~Window_();

        REQUIRES_SDL
        String getTitle(void);

        REQUIRES_SDL
        void setTitle(const String& title);

        REQUIRES_SDL
        void *getWMPointer(void);

        REQUIRES_SDL
        Optional<Window_::WMType> getWMType(void);

        static Window create(const Vec2i& size, const String& title, bool fullscreen = false);
        static Window createFullscreenDesktop(const String& title);
    };
}
#endif
