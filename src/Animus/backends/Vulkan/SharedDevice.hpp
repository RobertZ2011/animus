#ifndef ANIMUS_VULKAN_SHARED_DEVICE
#define ANIMUS_VULKAN_SHARED_DEVICE

#include "GraphicsDevice.hpp"
#include "ComputeDevice.hpp"

namespace Animus::Vulkan {
    class SharedDevice : public GraphicsDevice, public ComputeDevice {
    public:
        SharedDevice(Instance& instance, PhysicalDevice& device, const Window& window, bool vsync, uint32_t buffers);
        virtual ~SharedDevice(void);
    };
}

#endif