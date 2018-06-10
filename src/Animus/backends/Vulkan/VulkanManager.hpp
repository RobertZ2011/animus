#ifndef ANIMUS_VULKAN_MANAGER
#define ANIMUS_VULKAN_MANAGER

#include "functions.hpp"

#include <vulkan/vulkan.hpp>

#include "../../version.hpp"
#include "../../types.hpp"
#include "../../Singleton.hpp"
#include "../../SharedObject.hpp"
#include "../../Vector.hpp"

#include "DeviceQueuePool.hpp"

namespace Animus::Vulkan {
        Version convertVersion(uint32_t version);

    class VulkanManager : public Singleton<VulkanManager> {
        SharedObject so;
        vk::Instance instance;

        vk::Device graphicsDevice;
        vk::Device computeDevice;

        vk::DispatchLoaderDynamic instanceDispatch;
        vk::DispatchLoaderDynamic computeDispatch;
        vk::DispatchLoaderDynamic graphicsDispatch;

        UnsafeVector<vk::ExtensionProperties> instanceExtensions;
        UnsafeVector<vk::LayerProperties> instanceLayers;

        VulkanManager(void);
        void loadBaseFunctions(void);
        void createDevice(void);

        //heuristics for picking a device
        uint32_t calculateDeviceScore(const vk::PhysicalDevice& device);
        uint32_t calculateDeviceScore(const vk::PhysicalDeviceGroupProperties& deviceGroup);
    public:
        virtual ~VulkanManager(void);

        static void init(void);
        static void deinit(void);

        vk::Instance getInstance(void);

        bool hasLayer(const String& layer);
        bool hasExtension(const String& extension);

        UnsafeVector<const char*> getPlatformExtensions(void);
        Version getVersion(void);
    };
}
#endif
