UnsafeVector<const char*> VulkanManager::getPlatformExtensions(void) {
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
