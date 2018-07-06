#ifndef ANIMUS_VULKAN
#define ANIMUS_VULKAN

#include "../../Backend.hpp"

extern "C" Animus::Backend *create_backend(void);
extern "C" void destroy_backend(Animus::Backend *backend);

namespace Animus::Vulkan {
    Version convertVkVersion(uint32_t vkVersion);
    uint32_t convertVersion(const Version& version);
}

#endif