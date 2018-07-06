#include "../../../../macros.hpp"

namespace Animus::Vulkan {
    FilePath Backend::locateVulkan(void) {
        return FilePath("libvulkan.so");
    }

    UnsafeVector<const char*> Backend::getInstanceExtensions(void) {
        UnsafeVector<const char*> extensions = {"VK_KHR_surface"};

        #ifdef VK_USE_PLATFORM_XLIB_KHR
        extensions.push_back("VK_KHR_xlib_surface");
        #endif

        #ifdef VK_USE_PLATFORM_WAYLAND_KHR
        extensions.push_back("VK_KHR_wayland_surface");
        #endif

        return extensions;
    }

    REQUIRES_STD
    void Backend::createSurface(const Pointer<Window_>& window) {
        if(!window->getNativeWindowType()) {
            throw NoSurface("Cannot create Vulkan surface, unknown native window type");
        }

        auto nativeWindow = window->getNativeWindow();
        auto nativeType = window->getNativeWindowType().value();

        #ifdef VK_USE_PLATFORM_XLIB_KHR
        if(nativeType == Window_::WMType::X11) {
            vk::XlibSurfaceCreateInfoKHR info;
            auto xlibWindow = std::static_pointer_cast<XlibWindow_>(nativeWindow);

            info.window = xlibWindow->window;
            info.dpy = xlibWindow->display;

            this->surface = this->instance.createXlibSurfaceKHR(info, nullptr, this->dispatch);
            Log::getSingleton().logStr("Created Xlib Vulkan surface");
            return;
        }
        #endif

        #ifdef VK_USE_PLATFORM_WAYLAND_KHR
        if(nativeType == Window_::WMType::Wayland) {
            vk::WaylandSurfaceCreateInfoKHR info;
            auto waylandWindow = std::static_pointer_cast<WaylandWindow_>(nativeWindow);

            info.surface = waylandWindow->surface;
            info.display = waylandWindow->display;

            this->surface = this->instance.createWaylandSurfaceKHR(info, nullptr, this->dispatch);
            Log::getSingleton().logStr("Created Wayland Vulkan surface");
            return;
        }
        #endif


        throw NoSurface("Cannot create Vulkan surface, window is not an X11 or Wayland window");
    }
}