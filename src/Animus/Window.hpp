#ifndef ANIMUS_WINDOW
#define ANIMUS_WINDOW

#include "types/types.hpp"
#include "types/Vector.hpp"
#include "Backend.hpp"
#include "platform/Window.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    class Window_;
    typedef Pointer<Window_> Window;

    class Window_ {
    private:
        ANIMUS_REQUIRES_SDL
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

        ANIMUS_REQUIRES_SDL
        String getTitle(void);

        ANIMUS_REQUIRES_SDL
        void setTitle(const String& title);

        ANIMUS_REQUIRES_SDL
        NativeWindow getNativeWindow(void);

        ANIMUS_REQUIRES_SDL
        Optional<Window_::WMType> getNativeWindowType(void);

        ANIMUS_REQUIRES_SDL
        Vec2i getSize(void);

        static Window create(const Vec2i& size, const String& title, bool fullscreen = false);
        static Window createFullscreenDesktop(const String& title);
    };

    template<>
    String toString<Window_::WMType>(Window_::WMType type);
}
#endif
