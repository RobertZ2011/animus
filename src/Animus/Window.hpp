#ifndef ANIMUS_WINDOW
#define ANIMUS_WINDOW

#include "types/types.hpp"
#include "types/Vector.hpp"
#include "Backend.hpp"
#include "platform/Window.hpp"
#include "RenderTarget.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    class Window_;
    typedef Pointer<Window_> Window;

    class WindowProxy_ : public RenderTargetProxy_ {
        public:
        virtual ~WindowProxy_(void) = default;

        RenderTargetProxy_::Type getRenderTargetType(void) override;
        virtual void enableVsync(bool enabled) = 0;
        virtual void resize(const Vec2i& newSize) = 0;
        virtual void setBuffering(uint32_t count) = 0;
        virtual void setDisplayParams(const Vec2i& size, bool vsync, uint32_t buffers) = 0;
    };

    class Window_ : public RenderTarget_ {
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

        void enableVsync(bool enabled);
        void resize(const Vec2i& newSize);
        void setBuffering(uint32_t count);
        void setDisplayParams(const Vec2i& size, bool vsync, uint32_t buffers);

        static Window create(const Vec2i& size, const String& title, bool fullscreen = false);
        static Window createFullscreenDesktop(const String& title);

        RenderTargetProxy_::Type getRenderTargetType(void) override;
    };

    template<>
    String toString<Window_::WMType>(Window_::WMType type);
}
#endif
