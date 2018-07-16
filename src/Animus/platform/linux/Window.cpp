namespace Animus {
    ANIMUS_REQUIRES_SDL
    NativeWindow Window_::getNativeWindow(void) {
        Optional<WMType> type = this->getNativeWindowType();
        SDL_SysWMinfo info;
        XlibWindow_ *xWindow;
        WaylandWindow_ *wWindow;

        SDL_VERSION(&info.version);
        if(!type.has_value() || !SDL_GetWindowWMInfo(this->window, &info)) {
            Log::getSingleton().error("Failed to get native window info, %", SDL_GetError());
            throw RuntimeError("Failed to get native window handle");
        }

        switch(type.value()) {
            #ifdef SDL_VIDEO_DRIVER_X11
            case WMType::X11:
                xWindow = new XlibWindow_();
                xWindow->display = info.info.x11.display;
                xWindow->window = info.info.x11.window;

                return NativeWindow(xWindow);
                break;
            #endif

            #ifdef SDL_VIDEO_DRIVER_WAYLAND
            case WMType::Wayland:
                wWindow = new WaylandWindow_();
                wWindow->display = info.info.wl.display;
                wWindow->surface = info.info.wl.surface;

                return NativeWindow(wWindow);
                break;
            #endif

            default:
                Log::getSingleton().error("Failed to get native window handle, unsupported type %", type.value());
                throw RuntimeError("Failed to get native window handle");
        }
    }
}
