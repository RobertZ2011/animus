namespace Animus::Vulkan {
    REQUIRES_STD
    void WMInterface::createSurface(const NativeWindow& nativeWindow) {
        XlibWindow xWindow = std::dynamic_pointer_cast<XlibWindow_>(nativeWindow);
        WaylandWindow wWindow = std::dynamic_pointer_cast<WaylandWindow_>(nativeWindow);
        Optional<vk::SurfaceKHR> s;

        if(xWindow) {
            #ifdef VK_USE_PLATFORM_XLIB_KHR
                vk::XlibSurfaceCreateInfoKHR info;
                info.dpy = xWindow->display;
                info.window = xWindow->window;
                s = this->instance.createXlibSurfaceKHR(info, nullptr, this->dispatch);
            #endif
        }
        else
        if(wWindow) {
            #ifdef VK_USE_PLATFORM_WAYLAND_KHR
                vk::WaylandSurfaceCreateInfoKHR info;
                info.display = wWindow->display;
                info.surface = wWindow->surface;
                s = this->instance.createWaylandSurfaceKHR(info, nullptr, this->dispatch);
            #endif
        }
        else {
            Log::getSingleton().errorStr("Native window handle is not X11 or Wayland");
            throw RuntimeError("Native window handle is not X11 or Wayland");
        }

        if(!s.has_value()) {
            Log::getSingleton().errorStr("Failed to create vulkan surface");
            throw RuntimeError("Failed to create vulkan surface");
        }
        else {
            this->surface = s.value();
        }
    }
}
