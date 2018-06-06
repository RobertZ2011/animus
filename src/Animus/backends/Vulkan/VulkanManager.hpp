#ifndef ANIMUS_VULKAN_MANAGER
#define ANIMUS_VULKAN_MANAGER

#include "functions.hpp"

#include <vulkan/vulkan.hpp>

#include "../../version.hpp"
#include "../../types.hpp"
#include "../../Singleton.hpp"
#include "../../SharedObject.hpp"

namespace Animus {
namespace Vulkan {
    class VulkanManager : public Singleton<VulkanManager> {
        SharedObject so;
        vk::Instance instance;
        vk::DispatchLoaderDynamic instanceDispatch;

        UnsafeVector<vk::ExtensionProperties> instanceExceptions;
        UnsafeVector<vk::LayerProperties> instanceLayers;

        VulkanManager(void);
        void loadBaseFunctions(void);
    public:
        ~VulkanManager(void);

        static void init(void);
        static void deinit(void);

        vk::Instance getInstance(void);

        bool hasLayer(const String& layer);
        bool hasExtension(const String& extension);
    };
}
}
#endif
