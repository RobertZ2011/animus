//Abstraction of vulkan devices
#ifndef ANIMUS_VULKAN_DEVICE
#define ANIMUS_VULKAN_DEVICE

#include "../../types/Vector.hpp"
#include "../../Object.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

#include "Instance.hpp"
#include "PhysicalDevice.hpp"

namespace Animus::Vulkan {
    class Device : virtual public Object{
    protected:
        PhysicalDevice physicalDevice;
        vk::DispatchLoaderDynamic dispatch;
        vk::Device device;
        Instance& instance;

        UnsafeVector<vk::Queue> transferQueues;
        UnsafeVector<vk::Queue> workQueues;
        vk::CommandPool transferPool;
        vk::CommandPool workPool;
        uint32_t workFamily;
        uint32_t transferFamily;
        vk::Pipeline pipeline;

    public:
        Device(Instance& instance, PhysicalDevice& device);
        virtual ~Device(void);

        bool hasExtension(const String& name);
        vk::Device getDevice(void);
        vk::DispatchLoaderDynamic& getDispatch(void);
        bool isMulti(void);

        PhysicalDevice getPhysicalDevice(void);

    protected:
        void init(vk::QueueFlagBits workType);
        virtual UnsafeVector<const char*> getDeviceExtensions(void) = 0;
    };
}
#endif