#include "Window.hpp"
#include "Log.hpp"
#include "Error.hpp"

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

    Optional<Window_::WMType> Window_::getNativeWindowType(void) {
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);

        if(SDL_GetWindowWMInfo(this->window, &info)) {
            switch(info.subsystem) {
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

    Vec2i Window_::getSize(void) {
        Vec2i size;
        SDL_GetWindowSize(this->window, &size.x, &size.y);
        return size;
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

    template<>
    String toString<Window_::WMType>(Window_::WMType type) {
        switch(type){
            case Window_::WMType::X11:
                return String("X11");

            case Window_::WMType::Wayland:
                return String("Wayland");

            case Window_::WMType::Windows:
                return String("Windows");

            case Window_::WMType::Cocoa:
                return String("Cocoa");

            default:
                return String("Unknown");
        }
    }
}

#include "platform/Window.cpp"
