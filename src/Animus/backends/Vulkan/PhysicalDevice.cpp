#include "PhysicalDevice.hpp"
#include "../../macros/debug.hpp"
#include "../../types/Vector.hpp"

namespace Animus::Vulkan {
    PhysicalDevice_::PhysicalDevice_(const Instance& instance, vk::PhysicalDevice& device) : dispatch(instance->getDispatch()) {
        this->device = device;
    }
    
    PhysicalDevice_::PhysicalDevice_(const Instance& instance, vk::PhysicalDeviceGroupProperties& group) : dispatch(instance->getDispatch()) {
        this->group = group;
    }

    PhysicalDevice_::PhysicalDevice_(const PhysicalDevice_& other) : dispatch(other.dispatch) {
        *this = other;
    }

    PhysicalDevice_& PhysicalDevice_::operator=(const PhysicalDevice_& other) {
        this->group = other.group;
        this->device = other.device;
        return *this;
    }

    bool PhysicalDevice_::hasExtension(const String& name) {
        UnsafeVector<vk::ExtensionProperties> extensions;

        if(this->device) {
            extensions = this->device->enumerateDeviceExtensionProperties(nullptr, this->dispatch);
        }
        else {
            extensions = this->group->physicalDevices[0].enumerateDeviceExtensionProperties(nullptr, this->dispatch);
        }

        for(auto& extension: extensions) {
            if(extension.extensionName == name) {
                return true;
            }
        }

        return false;
    }

    uint32_t PhysicalDevice_::calculateScore(void) {
        if(this->device) {
            return calculateIndividualScore(this->device.value());
        }
        else
        if(this->group) {
            uint32_t sum = 0;
            for(uint32_t i = 0; i < this->group->physicalDeviceCount; i++) {
                sum += calculateIndividualScore(this->group->physicalDevices[i]);
            }

            //account for overhead in dealing with multiple devices
            return 95 * sum / 100;
        }
        else {
            return 0;
        }
    }

    bool PhysicalDevice_::isMulti(void) {
        return this->group.has_value();
    }

    vk::PhysicalDevice PhysicalDevice_::getDevice(void) {
        return this->device.value();
    }

    vk::PhysicalDeviceGroupProperties PhysicalDevice_::getGroup(void) {
        return this->group.value();
    }

    UnsafeVector<vk::QueueFamilyProperties> PhysicalDevice_::getQueueFamilies(void) {
        UnsafeVector<vk::QueueFamilyProperties> families;

        if(!this->isMulti()) {
            families = this->device->getQueueFamilyProperties(this->dispatch);
        }
        else {
            for(uint32_t i = 0; i < this->group->physicalDeviceCount; i++) {
                auto perDevice = this->group->physicalDevices[i].getQueueFamilyProperties(this->dispatch);

                for(auto& family: perDevice) {
                    families.push_back(family);
                }
            }
        }

        return families;
    }

    String PhysicalDevice_::getName(void) {
        if(this->isMulti()) {
            String name = "MultiDevice(";

            for(uint32_t i = 0; i < this->group->physicalDeviceCount; i++) {
                auto properties = this->group->physicalDevices[i].getProperties(this->dispatch);
                name += String(properties.deviceName) + ", ";
            }

            return name + ")";
        }
        else {
            auto properties = this->device->getProperties(this->dispatch);
            return String(properties.deviceName);
        }
    }

    Pointer<PhysicalDevice_> PhysicalDevice_::create(const Instance& instance, vk::PhysicalDevice& device) {
        auto ptr = Pointer<PhysicalDevice_>(new PhysicalDevice_(instance, device));
        ptr->self = ptr;
        return ptr;
    }

    Pointer<PhysicalDevice_> PhysicalDevice_::create(const Instance& instance, vk::PhysicalDeviceGroupProperties& group) {
        auto ptr = Pointer<PhysicalDevice_>(new PhysicalDevice_(instance, group));
        ptr->self = ptr;
        return ptr;
    }


    uint32_t PhysicalDevice_::calculateIndividualScore(vk::PhysicalDevice& device) {
        auto props = device.getProperties(this->dispatch);
        auto queueFamilies = device.getQueueFamilyProperties(this->dispatch);
        uint32_t sum = 0;

        sum += TYPE_SCORE[(int) props.deviceType];

        for(auto& queueFamily: queueFamilies) {
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eTransfer)) {
                sum += QUEUE_GCT * queueFamily.queueCount;
            }
            else
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eTransfer)) {
                sum += QUEUE_GT * queueFamily.queueCount;
            }
            else
            if(queueFamily.queueFlags & (vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eTransfer)) {
                sum += QUEUE_CT * queueFamily.queueCount;
            }
            else {
                sum += QUEUE_OTHER * queueFamily.queueCount;
            }
        }

        return sum;
    }
}