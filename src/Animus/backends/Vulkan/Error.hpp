#ifndef ANIMUS_VULKAN_ERROR
#define ANIMUS_VULKAN_ERROR

#include "../../Error.hpp"
#include "../../types.hpp"

namespace Animus::Vulkan {
    class NoInstanceExtension : public Exception {
        String extension;
    public:
        NoInstanceExtension(const String& extension);
        ~NoInstanceExtension(void) = default;

        const char *what(void) const noexcept override;
    };

    class NoSuitableDevice : public Exception {
    public:
        NoSuitableDevice(void) = default;
        ~NoSuitableDevice(void) = default;

        const char *what(void) const noexcept override;
    };

    class NoQueue : public Exception {
    public:
        NoQueue(void) = default;
        ~NoQueue(void) = default;

        const char *what(void) const noexcept override;
    };
}
#endif
