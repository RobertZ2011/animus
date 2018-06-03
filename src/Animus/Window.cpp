#include "Window.hpp"
#include "Graphics.hpp"
#include "Compute.hpp"

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

    String Window_::getTitle(void) {
        return "";
    }

    void Window_::setTitle(const String& title) {

    }

    GraphicsInterface Window_::createDefaultGraphicsInterface(void) {
        #ifdef ANIMUS_USE_VULKAN
        return Vulkan::GraphicsFactory().create(Window(this->self));
        #endif
    }

    ComputeInterface Window_::createDefaultComputeInterface(void) {
        #ifdef ANIMUS_USE_VULKAN
        return Vulkan::ComputeFactory().create(Window(this->self));
        #endif
    }

    /*Vector<GraphicsInterfaceFactory> Window_::getGraphicsInterfaces(void) {
        return {
            #ifdef ANIMUS_USE_VULKAN
            Vulkan::GraphicsFactory(),
            #endif
        };
    }

    Vector<ComputeInterfaceFactory> Window_::getComputeInterfaces(void) {
        return {
            #ifdef ANIMUS_USE_VULKAN
            Vulkan::ComputeFactory(),
            #endif
        };
    }*/

    Window Window_::create(const Vec2i& size, const String& title) {
        Window window(new Window_(size, title));
        window->self = WeakPtr<Window_>(window);
        return window;
    }
}
