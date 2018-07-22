namespace Animus::Vulkan {
    UnsafeVector<const char*> Instance_::getInstanceExtensions(void) {
        UnsafeVector<const char*> extensions = {"VK_KHR_surface"};

        #ifdef VK_USE_PLATFORM_XLIB_KHR
        extensions.push_back("VK_KHR_xlib_surface");
        #endif

        #ifdef VK_USE_PLATFORM_WAYLAND_KHR
        extensions.push_back("VK_KHR_wayland_surface");
        #endif

        return extensions;
    }
}