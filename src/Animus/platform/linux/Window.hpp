#ifndef ANIMUS_LINUX_WINDOW
#define ANIMUS_LINUX_WINDOW

namespace Animus {
    #ifdef SDL_VIDEO_DRIVER_X11
    struct XlibWindow_ : public NativeWindow_ {
        virtual ~XlibWindow_(void) = default;

        Display *display;
        ::Window window;
    };
    #else
    struct XlibWindow_ : public NativeWindow_ {
        virtual ~XlibWindow_(void) = default;
    };
    #endif

    typedef Pointer<XlibWindow_> XlibWindow;

    #ifdef SDL_VIDEO_DRIVER_WAYLAND
    struct WaylandWindow_ : public NativeWindow_ {
        virtual ~WaylandWindow_(void) = default;

        struct wl_display *display;
        struct wl_surface *surface;
    };
    #else
    struct WaylandWindow_ : public NativeWindow_ {
        virtual ~WaylandWindow_(void) = default;
    };
    #endif

    typedef Pointer<WaylandWindow_> WaylandWindow;
}

#endif
