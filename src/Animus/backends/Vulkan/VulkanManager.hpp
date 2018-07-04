#ifndef ANIMUS_VULKAN_MANAGER
#define ANIMUS_VULKAN_MANAGER

#include "functions.hpp"

#include <vulkan/vulkan.hpp>

#include "../../version.hpp"
#include "../../types.hpp"
#include "../../Singleton.hpp"
#include "../../SharedObject.hpp"
#include "../../Vector.hpp"
#include "../../macros.hpp"
#include "../../Window.hpp"

#include "DeviceQueuePool.hpp"
#include "SharedDevice.hpp"
#include "WMInterface.hpp"

namespace Animus::Vulkan {
        Version convertVersion(uint32_t version);

    class VulkanManager : public Singleton<VulkanManager> {
        SharedObject so;
        vk::Instance instance;
        WMInterface *wmInterface;

        DeviceQueuePool *computeDevice = nullptr;
        DeviceQueuePool *graphicsDevice = nullptr;

        SharedDevice *sharedDevice = nullptr;

        vk::DispatchLoaderDynamic dispatch;

        UnsafeVector<vk::ExtensionProperties> instanceExtensions;
        UnsafeVector<vk::LayerProperties> instanceLayers;

        VulkanManager(const NativeWindow& nativeWindow);
        void loadBaseFunctions(void);
        void createDevice(void);

        //heuristics for picking a device
        uint32_t calculateDeviceScore(const vk::PhysicalDevice& device);
        uint32_t calculateDeviceScore(const vk::PhysicalDeviceGroupProperties& deviceGroup);

        void createDevicePool(const vk::PhysicalDevice& device);
        void createDevicePool(const vk::PhysicalDeviceGroupProperties& deviceGroup);
    public:
        virtual ~VulkanManager(void);

        static void init(const NativeWindow& nativeWindow);
        static void deinit(void);

        vk::Instance& getInstance(void);
        vk::DispatchLoaderDynamic& getDispatch(void);

        bool hasLayer(const String& layer);
        bool hasExtension(const String& extension);
        bool hasExtension(const vk::PhysicalDevice& device, const String& str);

        UnsafeVector<const char*> getInstanceExtensions(void);
        UnsafeVector<const char*> getDeviceExtensions(const vk::PhysicalDevice& device);
        Version getVersion(void);
    };
}
#endif
