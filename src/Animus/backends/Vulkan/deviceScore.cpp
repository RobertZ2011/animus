#include "deviceScore.hpp"

//score per GB of RAM
//const uint32_t GRAPHICS_GB = 8;
//const uint32_t COMPUTE_GB = 8;

//score per device type for other, intgerated gpu, discete gpu, virtual gpu, cpu
const uint32_t GRAPHICS_DEVICE[] = {4, 8, 16, 16, 1};
const uint32_t COMPUTE_DEVICE[] = {4, 8, 16, 16, 2};

//scores for queue families
const uint32_t GRAPHICS_GCT = 8;
const uint32_t COMPUTE_GCT = 8;
const uint32_t GRAPHICS_GT = 16;
const uint32_t COMPUTE_CT = 16;

namespace Animus::Vulkan {
    uint32_t calculateDeviceScoreGraphics(const vk::PhysicalDevice& device, const vk::DispatchLoaderDynamic& loader) {
        auto props = device.getProperties();
        auto queueFamilies = device.getQueueFamilyProperties();
        uint32_t sum = 0;

        sum += GRAPHICS_DEVICE[(int) props.deviceType];

        for(auto& queueFamily: queueFamilies) {
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eTransfer)) {
                sum += GRAPHICS_GT * queueFamily.queueCount;
            }
            else
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eTransfer)) {
                sum += GRAPHICS_GCT * queueFamily.queueCount;
            }
        }

        return sum;
    }

    uint32_t calculateDeviceScoreGraphics(const vk::PhysicalDeviceGroupProperties& group, const vk::DispatchLoaderDynamic loader) {
        uint32_t sum = 0;
        for(uint32_t i = 0; i < group.physicalDeviceCount; i++) {
            sum += calculateDeviceScoreGraphics(group.physicalDevices[i], loader);
        }
        return sum;
    }

    uint32_t calculateDeviceScoreCompute(const vk::PhysicalDevice& device, const vk::DispatchLoaderDynamic loader) {
        auto props = device.getProperties();
        auto queueFamilies = device.getQueueFamilyProperties();
        uint32_t sum = 0;

        sum += COMPUTE_DEVICE[(int) props.deviceType];

        for(auto& queueFamily: queueFamilies) {
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eTransfer)) {
                sum += COMPUTE_CT * queueFamily.queueCount;
            }
            else
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eTransfer)) {
                sum += COMPUTE_GCT * queueFamily.queueCount;
            }
        }

        return sum;
    }

    uint32_t calculateDeviceScoreCompute(const vk::PhysicalDeviceGroupProperties& group, const vk::DispatchLoaderDynamic loader) {
        uint32_t sum = 0;
        for(uint32_t i = 0; i < group.physicalDeviceCount; i++) {
            sum += calculateDeviceScoreCompute(group.physicalDevices[i], loader);
        }
        return sum;
    }
}