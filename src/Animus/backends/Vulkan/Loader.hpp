#ifndef ANIMUS_VULKAN_LOADER
#define ANIMUS_VULKAN_LOADER

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

#include "../../version.hpp"
#include "../../types.hpp"
#include "../../Singleton.hpp"
#include "../../SharedObject.hpp"

extern Animus::SharedFunction<PFN_vkVoidFunction(VkInstance, const char*)> vkGetInstanceProcAddr;
extern PFN_vkCreateInstance vkCreateInstance;
extern PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
extern PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
extern PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;

namespace Animus {
namespace Vulkan {
    class Loader : public Singleton<Loader> {
        SharedObject so;

        Loader(void);
    public:
        ~Loader(void);

        void loadBaseFunctions(void);

        static void init(void);
        static void deinit(void);
    };
}
}
#endif
