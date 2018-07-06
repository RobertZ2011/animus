#ifndef ANIMUS_VULKAN_DEVICE_SCORE
#define ANIMUS_VULKAN_DEVICE_SCORE

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    uint32_t calculateDeviceScoreGraphics(const vk::PhysicalDevice& device, const vk::DispatchLoaderDynamic& loader);
    uint32_t calculateDeviceScoreGraphics(const vk::PhysicalDeviceGroupProperties& group, const vk::DispatchLoaderDynamic loader);

    uint32_t calculateDeviceScoreCompute(const vk::PhysicalDevice& device, const vk::DispatchLoaderDynamic loader);
    uint32_t calculateDeviceScoreCompute(const vk::PhysicalDeviceGroupProperties& group, const vk::DispatchLoaderDynamic loader);
}
#endif