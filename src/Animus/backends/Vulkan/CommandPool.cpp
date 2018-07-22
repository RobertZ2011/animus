#include "CommandPool.hpp"
#include "CommandBuffer.hpp"
#include "Device.hpp"

#include "../../Lock.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    CommandPool_::CommandPool_(const Device& device, uint32_t family) {
        vk::CommandPoolCreateInfo info;

        this->device = device;
        info.queueFamilyIndex = family;
        this->pool = this->device->getDevice().createCommandPool(info, nullptr, this->device->getDispatch());
    }

    CommandPool_::~CommandPool_(void) {

    }

    Pointer<PrimaryCommandBuffer_> CommandPool_::createPrimaryBuffer(void) {
        Lock l(this->mutex);
        vk::CommandBufferAllocateInfo info;

        info.commandPool = this->pool;
        info.commandBufferCount = 1;
        info.level = vk::CommandBufferLevel::ePrimary;
        return PrimaryCommandBuffer_::create(this->device, this->self.lock(), this->device->getDevice().allocateCommandBuffers(info, this->device->getDispatch())[0]);
    }

    Pointer<SecondaryCommandBuffer_> CommandPool_::createSecondaryBuffer(void) {
        Lock l(this->mutex);
        vk::CommandBufferAllocateInfo info;

        info.commandPool = this->pool;
        info.commandBufferCount = 1;
        info.level = vk::CommandBufferLevel::eSecondary;
        return SecondaryCommandBuffer_::create(this->device, this->self.lock(), this->device->getDevice().allocateCommandBuffers(info, this->device->getDispatch())[0]);
    }

    Pointer<CommandPool_> CommandPool_::create(const Device& device, uint32_t family) {
        auto ptr = Pointer<CommandPool_>(new CommandPool_(device, family));
        ptr->self = ptr;
        return ptr;
    }

    vk::CommandPool CommandPool_::getPool(void) {
        return this->pool;
    }

    void CommandPool_::lock(void) {
        this->mutex.lock();
    }

    void CommandPool_::unlock(void) {
        this->mutex.unlock();
    }
}