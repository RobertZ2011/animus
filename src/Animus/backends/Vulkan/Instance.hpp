#ifndef ANIMUS_VULKAN_INSTANCE
#define ANIMUS_VULKAN_INSTANCE

#include "../../types/Vector.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class PhysicalDevice;
    class Instance {
        vk::Instance instance;
        vk::DispatchLoaderDynamic dispatch;

    public:
        Instance(void);
        ~Instance(void);

        vk::Instance getInstance(void);
        vk::DispatchLoaderDynamic& getDispatch(void);

        bool hasExtension(const String& name);

        UnsafeVector<PhysicalDevice> enumerateDevices(void);
        bool supportsMultiGPU(void);
    private:
        UnsafeVector<const char*> getInstanceExtensions(void);
    };
}
#endif