namespace Animus::Vulkan {
    void Swapchain::createSurface(const Window& window) {
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

            this->surface = this->instance.getInstance().createXlibSurfaceKHR(info, nullptr, this->instance.getDispatch());
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

            this->surface = this->instance.getInstance().createWaylandSurfaceKHR(info, nullptr, this->instance.getDispatch());
            Log::getSingleton().logStr("Created Wayland Vulkan surface");
            return;
        }
        #endif


        throw NoSurface("Cannot create Vulkan surface, window is not an X11 or Wayland window");
    }
}