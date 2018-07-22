#ifndef ANIMUS_PHYSICAL_DEVICE
#define ANIMUS_PHYSICAL_DEVICE

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

#include "Instance.hpp"

namespace Animus::Vulkan {
    //Abstraction around groups and device groups
    class PhysicalDevice_ {
        Optional<vk::PhysicalDevice> device;
        Optional<vk::PhysicalDeviceGroupProperties> group;
        vk::DispatchLoaderDynamic& dispatch;
        WeakPtr<PhysicalDevice_> self;

        //score for each device type
        const uint32_t TYPE_SCORE[5] = {4, 8, 16, 16, 2};

        //scores for different queue types
        const uint32_t QUEUE_GT = 16;
        const uint32_t QUEUE_CT = 16;
        const uint32_t QUEUE_GCT = 8;
        const uint32_t QUEUE_OTHER = 4;

    public:
        PhysicalDevice_(const PhysicalDevice_& other);
        ~PhysicalDevice_(void) = default;

        PhysicalDevice_& operator=(const PhysicalDevice_& other);

        bool hasExtension(const String& name);
        uint32_t calculateScore(void);
        bool isMulti(void);

        vk::PhysicalDevice getDevice(void);
        vk::PhysicalDeviceGroupProperties getGroup(void);

        UnsafeVector<vk::QueueFamilyProperties> getQueueFamilies(void);
        String getName(void);

        static Pointer<PhysicalDevice_> create(const Instance& instance, vk::PhysicalDevice& device);
        static Pointer<PhysicalDevice_> create(const Instance& instance, vk::PhysicalDeviceGroupProperties& group);

    private:
        uint32_t calculateIndividualScore(vk::PhysicalDevice& device);
        PhysicalDevice_(const Instance& instance, vk::PhysicalDevice& device);
        PhysicalDevice_(const Instance& instance, vk::PhysicalDeviceGroupProperties& group);
    };

    typedef Pointer<PhysicalDevice_> PhysicalDevice;
}
#endif