//Abstraction of vulkan devices
#ifndef ANIMUS_VULKAN_DEVICE
#define ANIMUS_VULKAN_DEVICE

#include "../../types/Vector.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

#include "Instance.hpp"
#include "PhysicalDevice.hpp"

namespace Animus::Vulkan {
    class PrimaryCommandBuffer_;
    class SecondaryCommandBuffer_;

    class Device_ {
    protected:
        PhysicalDevice physicalDevice;
        vk::DispatchLoaderDynamic dispatch;
        vk::Device device;
        Instance instance;
        WeakPtr<Device_> self;
        Mutex lock;

        UnsafeVector<vk::Queue> transferQueues;
        UnsafeVector<vk::Queue> workQueues;
        uint32_t workFamily;
        uint32_t transferFamily;
        vk::Pipeline pipeline;

    public:
        Device_(const Instance& instance, const PhysicalDevice& device);
        virtual ~Device_(void);

        bool hasExtension(const String& name);
        vk::Device getDevice(void);
        vk::DispatchLoaderDynamic& getDispatch(void);
        bool isMulti(void);

        PhysicalDevice getPhysicalDevice(void);

        void submitWork(const Pointer<PrimaryCommandBuffer_>& buffer);
        void submitTransfer(const Pointer<PrimaryCommandBuffer_>& buffer);

        Pointer<PrimaryCommandBuffer_> createPrimaryWorkBuffer(void);
        Pointer<SecondaryCommandBuffer_> createSecondaryWorkBuffer(void);

        Pointer<PrimaryCommandBuffer_> createPrimaryTrasferBuffer(void);
        Pointer<SecondaryCommandBuffer_> createSecondaryTransferBuffer(void);

    protected:
        void init(vk::QueueFlagBits workType);
        virtual UnsafeVector<const char*> getDeviceExtensions(void) = 0;
    };

    typedef Pointer<Device_> Device;
}
#endif