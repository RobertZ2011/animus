#include "Device.hpp"
#include "../../Log.hpp"

namespace Animus::Vulkan {
    Device_::Device_(const Instance& instance, const PhysicalDevice& device) : physicalDevice(device), instance(instance) {
        this->dispatch = instance->getDispatch();
    }

    Device_::~Device_(void) {
        this->device.destroy(nullptr, this->dispatch);
    }

    bool Device_::hasExtension(const String& name) {
        return this->physicalDevice->hasExtension(name);
    }

    vk::Device Device_::getDevice() {
        return this->device;
    }

    vk::DispatchLoaderDynamic& Device_::getDispatch(void) {
        return this->dispatch;
    }

    bool Device_::isMulti(void) {
        return this->physicalDevice->isMulti();
    }

    PhysicalDevice Device_::getPhysicalDevice(void) {
        return this->physicalDevice;
    }

    void Device_::init(vk::QueueFlagBits workType) {
        struct FamilyInfo {
            vk::QueueFamilyProperties props;
            uint32_t index;

            FamilyInfo(vk::QueueFamilyProperties props, uint32_t index) {
                this->index = index;
                this->props = props;
            }
        };

        auto families = this->physicalDevice->getQueueFamilies();
        vk::DeviceCreateInfo info;
        vk::CommandPoolCreateInfo commandInfo;
        UnsafeVector<const char*> extensions = this->getDeviceExtensions();
        UnsafeVector<FamilyInfo> workAvail;
        UnsafeVector<FamilyInfo> transferAvail;
        UnsafeVector<FamilyInfo> mixedAvail;
        UnsafeVector<vk::DeviceQueueCreateInfo> queueInfo;

        //see what queues are available, seperate them into mixed and dedicated
        for(uint32_t i = 0; i < families.size(); i++) {
            UnsafeVector<FamilyInfo> *targetQueue;
            auto& family = families[i];

            if((family.queueFlags & (workType | vk::QueueFlagBits::eTransfer)) == (workType | vk::QueueFlagBits::eTransfer)) {
                targetQueue = &mixedAvail;
            }
            else
            if(family.queueFlags & workType) {
                targetQueue = &workAvail;
            }
            else
            if(family.queueFlags & vk::QueueFlagBits::eTransfer) {
                targetQueue = &transferAvail;
            }
            else {
                break;
            }

            targetQueue->push_back(FamilyInfo(family, i));
        }

        //sort queues by queueCount
        auto queueSort = [](FamilyInfo& a , FamilyInfo& b) {
            return a.props.queueCount < b.props.queueCount;
        };

        std::sort(workAvail.begin(), workAvail.end(), queueSort);
        std::sort(mixedAvail.begin(), mixedAvail.end(), queueSort);
        std::sort(transferAvail.begin(), transferAvail.end(), queueSort);

        //if we can't find queues to support graphics and transfers
        if(mixedAvail.size() == 0 && (workAvail.size() == 0 || transferAvail.size() == 0)) {
            Log::getSingleton().errorStr("Cannot find queues to support both graphics and transfer");
            ANIMUS_TODO("Throw exception");
        }

        //if we only have a single, mixed queue family
        if(mixedAvail.size() == 1 && workAvail.size() == 0 && transferAvail.size() == 0) {
            this->workFamily = mixedAvail.back().index;
            this->transferFamily = this->workFamily;
        }
        else {
            if(workAvail.size() != 0) {
                this->workFamily = workAvail.back().index;
            }
            else {
                this->workFamily = mixedAvail.back().index;
                mixedAvail.pop_back();

            }

            if(transferAvail.size() != 0) {
                this->transferFamily = transferAvail.back().index;
            }
            else {
                this->transferFamily = mixedAvail.back().index;
                mixedAvail.pop_back();
            }
        }


        //device extensions
        info.enabledExtensionCount = extensions.size();
        info.ppEnabledExtensionNames = &extensions[0];

        //queue info
        if(this->workFamily == this->transferFamily) {
            vk::DeviceQueueCreateInfo queueCreate;
            uint32_t count = families[this->workFamily].queueCount;
            float *priorities = (float*) alloca(sizeof(float) * count);

            for(uint32_t i = 0; i < count; i++) {
                priorities[i] = 1.0f;
            }

            queueCreate.queueFamilyIndex = this->workFamily;
            queueCreate.queueCount = count;
            queueCreate.pQueuePriorities = priorities;
            queueInfo.push_back(queueCreate);
        }
        else {
            vk::DeviceQueueCreateInfo workCreate;
            vk::DeviceQueueCreateInfo transferCreate;
            uint32_t workCount = families[this->workFamily].queueCount;
            uint32_t transferCount = families[this->transferFamily].queueCount;
            float *workPriorities = (float*) alloca(sizeof(float) * workCount);
            float *transferPriorities = (float*)  alloca(sizeof(float) * transferCount);

            for(uint32_t i = 0; i < workCount; i++) {
                workPriorities[i] = 1.0f;
            }

            for(uint32_t i = 0; i < transferCount; i++) {
                transferPriorities[i] = 0.9f;
            }

            workCreate.queueFamilyIndex = this->workFamily;
            workCreate.queueCount = workCount;
            workCreate.pQueuePriorities = workPriorities;

            transferCreate.queueFamilyIndex = this->transferFamily;
            transferCreate.queueCount = transferCount;
            transferCreate.pQueuePriorities = transferPriorities;

            queueInfo.push_back(workCreate);
            queueInfo.push_back(transferCreate);
        }

        info.queueCreateInfoCount = queueInfo.size();
        info.pQueueCreateInfos = &queueInfo[0];

        if(this->physicalDevice->isMulti()) {
            ANIMUS_TODO("implement this");
        }
        else {
            this->device = this->physicalDevice->getDevice().createDevice(info, nullptr, instance->getDispatch());
        }
        
        this->dispatch = vk::DispatchLoaderDynamic(instance->getInstance(), this->device);

        //get the queues
        if(this->workFamily == this->transferFamily) {
            vk::Queue queue;

            for(uint32_t i = 0; i < families[this->workFamily].queueCount; i++) {
                queue = this->device.getQueue(this->workFamily, i, this->dispatch);
                this->workQueues.push_back(queue);
                this->transferQueues.push_back(queue);
            }
        }
        else {
            for(uint32_t i = 0; i < families[this->workFamily].queueCount; i++) {
                auto queue = this->device.getQueue(this->workFamily, i, this->dispatch);
                this->workQueues.push_back(queue);
            }

            for(uint32_t i = 0; i < families[this->transferFamily].queueCount; i++) {
                auto queue = this->device.getQueue(this->transferFamily, i, this->dispatch);
                this->transferQueues.push_back(queue);
            }
        }
        
        Log::getSingleton().log("Created graphics device on % with % work and % transfer queues", this->physicalDevice->getName(), this->workQueues.size(), this->transferQueues.size());
    }
 }