#include "SharedDeviceQueuePool.hpp"
#include "VulkanManager.hpp"
#include "Error.hpp"
#include "../../Vector.hpp"
#include "../../types.hpp"
#include "../../Log.hpp"

namespace Animus::Vulkan {
    SharedDeviceQueuePool::SharedDeviceQueuePool(const vk::PhysicalDevice& device, VulkanManager *manager) {
        this->init(device, manager);
    }

    SharedDeviceQueuePool::SharedDeviceQueuePool(const vk::PhysicalDeviceGroupProperties& deviceGroup, VulkanManager *manager) {
        vk::DeviceGroupDeviceCreateInfo info;

        info.physicalDeviceCount = deviceGroup.physicalDeviceCount;
        info.pPhysicalDevices = deviceGroup.physicalDevices;

        this->init(deviceGroup.physicalDevices[0], manager, &info);
        this->setupSurfaceFormat();
    }

    SharedDeviceQueuePool::~SharedDeviceQueuePool(void) {

    }

    void SharedDeviceQueuePool::init(const vk::PhysicalDevice& physicalDevice, VulkanManager *manager, vk::DeviceGroupDeviceCreateInfo *groupInfo) {
        vk::DeviceCreateInfo info;
        UnsafeVector<vk::DeviceQueueCreateInfo> queueInfo;
        UnorderedMap<uint32_t, uint32_t> queueUsage;
        auto queueProps = device.getQueueFamilyProperties(manager->getDispatch());
        uint32_t transferQueueCount = 0;
        UnsafeVector<uint32_t> transferFamilies;
        Optional<uint32_t> graphicsFamily;
        Optional<uint32_t> computeFamily;
        uint32_t transferCount = 0;
        auto deviceExtensions = manager->getDeviceExtensions(physicalDevice);

        if(groupInfo) {
            info.pNext = reinterpret_cast<void*>(groupInfo);
        }

        //put all device family indicies into queueUsage
        for(uint32_t i = 0; i < queueProps.size(); i++) {
            queueUsage[i] = 0;
        }

        //get our graphics queue
        for(uint32_t i = 0; i < queueProps.size(); i++) {
            auto& prop = queueProps[i];
            if(prop.queueFlags & vk::QueueFlagBits::eGraphics) {
                //don't have to do anything fancy since this is the first queue
                queueUsage[i]++;
                graphicsFamily = i;
                break;
            }
        }

        if(!graphicsFamily.has_value()) {
            Log::getSingleton().errorStr("Failed to find graphics queue");
            throw NoQueue();
        }

        //get our compute queue
        for(uint32_t i = 0; i < queueProps.size(); i++) {
            auto& prop = queueProps[i];
            if(prop.queueFlags & vk::QueueFlagBits::eCompute) {
                if(queueUsage[i] + 1 <= prop.queueCount) {
                    queueUsage[i]++;
                    computeFamily = i;
                    break;
                }
            }
        }

        if(!computeFamily.has_value()) {
            Log::getSingleton().errorStr("Failed to find compute queue");
            throw NoQueue();
        }

        //get up to 8 transfer queues
        for(uint32_t i = 0; i < queueProps.size(); i++) {
            auto& prop = queueProps[i];
            if(prop.queueFlags & vk::QueueFlagBits::eTransfer) {
                if(queueUsage[i] < prop.queueCount) {
                    transferQueueCount += prop.queueCount - queueUsage[i];
                    //use up the rest
                    queueUsage[i] = prop.queueCount;

                    if(transferQueueCount > SharedDeviceQueuePool::MAX_TRANSFER_QUEUES) {
                        break;
                    }
                }
            }
        }

        if(transferQueueCount == 0) {
            Log::getSingleton().errorStr("Failed to find transfer queue");
            throw NoQueue();
        }

        //setup our queue creation info
        for(uint32_t i = 0; i < queueProps.size(); i++) {
            if(queueUsage[i] > 0) {
                float *priorities = new float[queueUsage[i]];
                vk::DeviceQueueCreateInfo creationInfo;

                creationInfo.queueFamilyIndex = i;
                creationInfo.queueCount = queueUsage[i];
                creationInfo.pQueuePriorities = priorities;

                if(graphicsFamily == i && computeFamily == i) {
                    //both compute and graphics are on this family, make the first
                    //two priorities equal and the highest
                    priorities[0] = 1.0f;
                    priorities[1] = 1.0f;
                    for(int j = 2; j < queueUsage[i]; j++) {
                        priorities[j] = 0.5f;
                    }
                }
                else {
                    //first queue has highest priority
                    priorities[0] = 1.0f;
                    for(int j = 1; j < queueUsage[i]; j++) {
                        priorities[j] = 0.5f;
                    }
                }


                queueInfo.push_back(creationInfo);
            }
        }

        info.queueCreateInfoCount = queueInfo.size();
        info.pQueueCreateInfos = &queueInfo[0];

        info.enabledExtensionCount = deviceExtensions.size();
        info.ppEnabledExtensionNames = &deviceExtensions[0];

        this->device = physicalDevice.createDevice(info, nullptr, manager->getDispatch());
        this->dispatch = manager->getDispatch();

        Log::getSingleton().log("Created shared logical device with % transfer queues", transferQueueCount);

        //get our queues
        if(graphicsFamily == computeFamily) {
            //the first two queue are our graphics and compute queues
            this->graphicsQueue = this->device.getQueue(graphicsFamily.value(), 0, this->dispatch);
            this->computeQueue = this->device.getQueue(computeFamily.value(), 1, this->dispatch);
        }
        else {
            this->graphicsQueue = this->device.getQueue(graphicsFamily.value(), 0, this->dispatch);
            this->computeQueue = this->device.getQueue(computeFamily.value(), 0, this->dispatch);
        }

        //get our transfer queues
        for(uint32_t family: transferFamilies) {
            uint32_t start = 0;

            if(family == graphicsFamily.value() && graphicsFamily == computeFamily) {
                start = 2;
            }
            else
            if(family == graphicsFamily.value() || family == computeFamily.value()) {
                start = 1;
            }

            for(uint32_t i = start; i < queueUsage[i]; i++, transferCount++) {
                this->transferQueue[transferCount] = this->device.getQueue(family, i, this->dispatch);
            }
        }
    }
}
