#include "vulkan.hpp"
#include "Backend.hpp"

Animus::Backend *create_backend(void) {
    return new Animus::Vulkan::Backend();
}

void destroy_backend(Animus::Backend *backend) {
    delete backend;
}

namespace Animus::Vulkan {
    Version convertVkVersion(uint32_t vkVersion) {
        uint32_t major = (vkVersion >> 22) & 0x3FF;
        uint32_t minor = (vkVersion >> 12) & 0x3FF;
        uint32_t patch = vkVersion & 0xFFF;

        return Version(major, minor, patch);
    }

    uint32_t convertVersion(const Version& version) {
        return 0;
    }
}