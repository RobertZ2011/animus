#include "Loader.hpp"

Animus::SharedFunction<PFN_vkVoidFunction(VkInstance, const char*)> vkGetInstanceProcAddr;
PFN_vkCreateInstance vkCreateInstance = nullptr;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties = nullptr;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties = nullptr;
PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion = nullptr;

namespace Animus {
namespace Vulkan {
    Loader::Loader(void) {
        this->so = SharedObject_::create("libvulkan.so");
        vkGetInstanceProcAddr = this->so->loadFunction<PFN_vkVoidFunction(VkInstance, const char*)>("vkGetInstanceProcAddr");
    }

    Loader::~Loader(void) {
        //Clear this pointer so that the sharedobject will release
        vkGetInstanceProcAddr.destroy();
    }

    void Loader::loadBaseFunctions(void) {
        vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(vkGetInstanceProcAddr(nullptr, "vkCreateInstance"));
        vkEnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties"));
        vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties"));
        vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
    }

    void Loader::init(void) {
        Loader::initSingleton(new Loader());
    }

    void Loader::deinit(void) {
        Loader::deinitSingleton();
    }

}
}
