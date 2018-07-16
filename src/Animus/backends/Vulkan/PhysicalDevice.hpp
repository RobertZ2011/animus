#ifndef ANIMUS_PHYSICAL_DEVICE
#define ANIMUS_PHYSICAL_DEVICE

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

#include "Instance.hpp"

namespace Animus::Vulkan {
    //Abstraction around groups and device groups
    class PhysicalDevice {
        Optional<vk::PhysicalDevice> device;
        Optional<vk::PhysicalDeviceGroupProperties> group;
        vk::DispatchLoaderDynamic& dispatch;

        //score for each device type
        const uint32_t TYPE_SCORE[5] = {4, 8, 16, 16, 2};

        //scores for different queue types
        const uint32_t QUEUE_GT = 16;
        const uint32_t QUEUE_CT = 16;
        const uint32_t QUEUE_GCT = 8;
        const uint32_t QUEUE_OTHER = 4;

    public:
        PhysicalDevice(Instance& instance, vk::PhysicalDevice& device);
        PhysicalDevice(Instance& instance, vk::PhysicalDeviceGroupProperties& group);
        PhysicalDevice(const PhysicalDevice& other);
        ~PhysicalDevice(void) = default;

        PhysicalDevice& operator=(const PhysicalDevice& other);

        bool hasExtension(const String& name);
        uint32_t calculateScore(void);
        bool isMulti(void);

        vk::PhysicalDevice getDevice(void);
        vk::PhysicalDeviceGroupProperties getGroup(void);

        UnsafeVector<vk::QueueFamilyProperties> getQueueFamilies(void);
        String getName(void);

    private:
        uint32_t calculateIndividualScore(vk::PhysicalDevice& device);
    };
}
#endif