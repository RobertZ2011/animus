#include "CommandBuffer.hpp"
#include "CommandPool.hpp"
#include "Device.hpp"

namespace Animus::Vulkan {
    CommandBuffer_::CommandBuffer_(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer) {
        this->device = device;
        this->pool = pool;
        this->buffer = buffer;
    }

    CommandBuffer_::~CommandBuffer_(void) {
        if(this->buffer) {
        }
    }

    SecondaryCommandBuffer_::SecondaryCommandBuffer_(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer) : CommandBuffer_(device, pool, buffer) {

    }

    Pointer<SecondaryCommandBuffer_> SecondaryCommandBuffer_::create(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer) {
        auto ptr = Pointer<SecondaryCommandBuffer_>(new SecondaryCommandBuffer_(device, pool, buffer));
        return ptr;
    }

    PrimaryCommandBuffer_::PrimaryCommandBuffer_(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer) : CommandBuffer_(device, pool, buffer) {

    }

    void PrimaryCommandBuffer_::attachSecondary(const SecondaryCommandBuffer& buffer) {

    }

    Pointer<PrimaryCommandBuffer_> PrimaryCommandBuffer_::create(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer) {
        auto ptr = Pointer<PrimaryCommandBuffer_>(new PrimaryCommandBuffer_(device, pool, buffer));
        return ptr;
    }
}