#ifndef ANIMUS_VULKAN_SHARED_DEVICE_ADAPTER
#define ANIMUS_VULKAN_SHARED_DEVICE_ADAPTER

#include "DeviceQueuePool.hpp"

namespace Animus::Vulkan {
    //allows a SharedDeviceQueuePool to act as two individual DeviceQueuePools
    class SharedDeviceAdapter : public DeviceQueuePool {

    };
}
#endif
