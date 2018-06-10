#include "Window.hpp"
#include <SDL2/SDL_syswm.h>

namespace Animus {
    Window_::Window_(const Vec2i& size, const String& title, bool fullscreen) {
        uint32_t flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

        this-> window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            size.x,
            size.y,
            flags
        );
    }

    Window_::Window_(const String& title) {
        this-> window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            -1,
            -1,
            SDL_WINDOW_FULLSCREEN_DESKTOP
        );
    }

    Window_::~Window_() {
        if(this->window) {
            SDL_DestroyWindow(this->window);
        }
    }

    String Window_::getTitle(void) {
        return String(SDL_GetWindowTitle(this->window));
    }

    void Window_::setTitle(const String& title) {
        SDL_SetWindowTitle(this->window, title.c_str());
    }

    void *Window_::getWMPointer(void) {
        auto type = this->getWMType();
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);

        if(!type) {
            return nullptr;
        }

        if(!SDL_GetWindowWMInfo(this->window, &info)) {
            return nullptr;
        }

        switch(type.value()) {
            case Window_::WMType::Windows:
                #ifdef SDL_VIDEO_DRIVER_WINDOWS
                return reinterpret_cast<void*>(info.info.win.hwnd);
                #else
                return nullptr;
                #endif

            case Window_::WMType::X11:
                #ifdef SDL_VIDEO_DRIVER_X11
                return reinterpret_cast<void*>(info.info.x11.window);
                #else
                return nullptr;
                #endif

            case Window_::WMType::Cocoa:
                #ifdef SDL_VIDEO_DRIVER_COCOA
                return reinterpret_cast<void*>(info.info.cocoa.window);
                #else
                return nullptr;
                #endif

            case Window_::WMType::Wayland:
                #ifdef SDL_VIDEO_DRIVER_WAYLAND
                return reinterpret_cast<void*>(info.info.wl.surface);
                #else
                return nullptr;
                #endif

            default:
                return nullptr;
        }
    }

    Optional<Window_::WMType> Window_::getWMType(void) {
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);

        if(SDL_GetWindowWMInfo(this->window, &info)) {
            switch(info.subsystem) {
                case SDL_SYSWM_UNKNOWN:
                    return Optional<Window_::WMType>();

                case SDL_SYSWM_WINDOWS:
                    return Optional<Window_::WMType>(Window_::WMType::Windows);

                case SDL_SYSWM_X11:
                    return Optional<Window_::WMType>(Window_::WMType::X11);

                case SDL_SYSWM_COCOA:
                    return Optional<Window_::WMType>(Window_::WMType::Cocoa);

                case SDL_SYSWM_WAYLAND:
                    return Optional<Window_::WMType>(Window_::WMType::Wayland);

                default:
                    return Optional<Window_::WMType>();
            }
        }
        else {
            return Optional<Window_::WMType>();
        }
    }

    Window Window_::create(const Vec2i& size, const String& title, bool fullscreen) {
        Window window(new Window_(size, title, fullscreen));
        window->self = WeakPtr<Window_>(window);
        return window;
    }

    Window Window_::createFullscreenDesktop(const String& title) {
        Window window(new Window_(title));
        window->self = WeakPtr<Window_>(window);
        return window;
    }
}
