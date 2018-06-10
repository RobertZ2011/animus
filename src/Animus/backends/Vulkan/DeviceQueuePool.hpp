#ifndef ANIMUS_QUEUE_POOL
#define ANIMUS_QUEUE_POOL

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
        //easily dispatch work among multiple queues
        class DeviceQueuePool {
        public:
            DeviceQueuePool(void) = default;
            virtual ~DeviceQueuePool(void) = default;
        };
}
#endif
