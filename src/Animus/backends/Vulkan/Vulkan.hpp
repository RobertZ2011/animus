#ifndef ANIMUS_VULKAN
#define ANIMUS_VULKAN

#include "../../Backend.hpp"
#include "../../Window.hpp"

extern "C" Backend *createBackend(void);
extern "C" void destroyBackend(Backend *backend);

#endif
