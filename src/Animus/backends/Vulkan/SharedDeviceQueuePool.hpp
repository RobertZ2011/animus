#ifndef ANIMUS_VULKAN_SHARED_DEVICE_QUEUE_POOL
#define ANIMUS_VULKAN_SHARED_DEVICE_QUEUE_POOL

namespace Animus::Vulkan {
    //manages grahpics and compute queues on a single device
    class SharedDeviceQueuePool {
    public:
        SharedDeviceQueuePool(const vk::PhysicalDevice& device);
        SharedDeviceQueuePool(const vk::PhysicalDeviceGroupProperties& deviceGroup);
        virtual ~SharedDeviceQueuePool(void);
    };
}
#endif
