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

    const char *NoQueue::what(void) const noexcept {
        return "Failed to find suitable queue";
    }
}
