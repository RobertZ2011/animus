#ifndef ANIMUS_VULKAN_SHARED_DEVICE_QUEUE_POOL
#define ANIMUS_VULKAN_SHARED_DEVICE_QUEUE_POOL

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class VulkanManager;

    //manages grahpics and compute queues on a single device
    class SharedDeviceQueuePool {
        vk::Device device;
        vk::Queue computeQueue;
        vk::Queue graphicsQueue;
        vk::Queue transferQueue[8];
        vk::DispatchLoaderDynamic dispatch;
        Optional<vk::SwapchainKHR> swapchain;

        const int MAX_TRANSFER_QUEUES = 8;

        void init(const vk::PhysicalDevice& device, VulkanManager *manager, vk::DeviceGroupDeviceCreateInfo *groupInfo = nullptr);

    public:
        SharedDeviceQueuePool(const vk::PhysicalDevice& device, VulkanManager *manager);
        SharedDeviceQueuePool(const vk::PhysicalDeviceGroupProperties& deviceGroup, VulkanManager *manager);
        virtual ~SharedDeviceQueuePool(void);
    };
}
#endif
