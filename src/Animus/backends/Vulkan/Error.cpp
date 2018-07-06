#include "Error.hpp"

namespace Animus::Vulkan {
    NoInstanceExtension::NoInstanceExtension(const String& extension) {
        this->extension = extension;
    }

    const char *NoInstanceExtension::what(void) const noexcept {
        return this->extension.c_str();
    }

    const char *NoSuitableDevice::what(void) const noexcept {
        return "Failed to find suitable device";
    }

    NoSurface::NoSurface(const String& reason) {
        this->reason = reason;
    }

    const char *NoSurface::what(void) const noexcept {
        return this->reason.c_str();
    }

    const char *NoQueue::what(void) const noexcept {
        return "Failed to find suitable queue";
    }
}
