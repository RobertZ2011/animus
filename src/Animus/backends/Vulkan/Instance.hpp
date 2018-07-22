#ifndef ANIMUS_VULKAN_INSTANCE
#define ANIMUS_VULKAN_INSTANCE

#include "../../types/Vector.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class PhysicalDevice_;
    class Instance_ {
        vk::Instance instance;
        vk::DispatchLoaderDynamic dispatch;
        WeakPtr<Instance_> self;

    public:
        ~Instance_(void);

        vk::Instance getInstance(void);
        vk::DispatchLoaderDynamic& getDispatch(void);

        bool hasExtension(const String& name);

        UnsafeVector<Pointer<PhysicalDevice_>> enumerateDevices(void);
        bool supportsMultiGPU(void);

        static Pointer<Instance_> create(void);
    private:
        Instance_(void);
        UnsafeVector<const char*> getInstanceExtensions(void);
    };

    typedef Pointer<Instance_> Instance;
}
#endif