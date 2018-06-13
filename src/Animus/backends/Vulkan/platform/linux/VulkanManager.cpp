namespace Animus::Vulkan {
    UnsafeVector<const char*> VulkanManager::getInstanceExtensions(void) {
        int surfaceExtensions = 0;
        UnsafeVector<const char*> extensions;

        //VK_KHR_surface is required
        if(this->hasExtension("VK_KHR_surface")) {
            extensions.push_back("VK_KHR_surface");
        }
        else {
            Log::getSingleton().errorStr("Vulkan instance does not support VK_KHR_surface");
            throw NoInstanceExtension("VK_KHR_surface");
        }

        if(this->hasExtension("VK_KHR_xlib_surface")) {
            extensions.push_back("VK_KHR_xlib_surface");
            surfaceExtensions++;
        }

        if(this->hasExtension("VK_KHR_xcb_surface")) {
            extensions.push_back("VK_KHR_xcb_surface");
            surfaceExtensions++;
        }

        if(this->hasExtension("VK_KHR_wayland_surface")) {
            extensions.push_back("VK_KHR_wayland_surface");
            surfaceExtensions++;
        }

        if(this->hasExtension("VK_KHR_mir_surface")) {
            extensions.push_back("VK_KHR_mir_surface");
            surfaceExtensions++;
        }

        if(surfaceExtensions == 0) {
            Log::getSingleton().errorStr("Failed to find any surface extensions");
            throw NoInstanceExtension("Linux surface extensions");
        }

        return extensions;
    }

    UnsafeVector<const char*> VulkanManager::getDeviceExtensions(const vk::PhysicalDevice& device) {
        auto extensionInfo = device.enumerateDeviceExtensionProperties(nullptr, this->dispatch);
        UnsafeVector<const char*> extensions;

        if(this->hasExtension(device, "VK_KHR_swapchain")) {
            extensions.push_back("VK_KHR_swapchain");
        }
        else {
            Log::getSingleton().errorStr("Vulkan physical device does not support VK_KHR_swapchain");
            throw NoInstanceExtension("VK_KHR_swapchain");
        }

        return extensions;
    }

    REQUIRES_STD
    void VulkanManager::createSurface(const NativeWindow& nativeWindow) {
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
