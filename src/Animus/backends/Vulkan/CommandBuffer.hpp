#ifndef ANIMUS_VULKAN_COMMAND_BUFFER
#define ANIMUS_VULKAN_COMMAND_BUFFER

#include "../../types/types.hpp"
#include "../../Mutex.hpp"
#include "../../types/Vector.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class CommandPool_;
    class Device_;

    class CommandBuffer_ {
    protected:
        Mutex lock;
        Pointer<CommandPool_> pool;
        Pointer<Device_> device;
        vk::CommandBuffer buffer;

        CommandBuffer_(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer);
    
    public:
        virtual ~CommandBuffer_(void);
    };

    typedef Pointer<CommandBuffer_> CommandBuffer;

    class SecondaryCommandBuffer_ : public CommandBuffer_ {
    public:
        virtual ~SecondaryCommandBuffer_(void) = default;

        static Pointer<SecondaryCommandBuffer_> create(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer);

    private:
        SecondaryCommandBuffer_(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer);
    };

    typedef Pointer<SecondaryCommandBuffer_> SecondaryCommandBuffer;

    class PrimaryCommandBuffer_ : public CommandBuffer_ {
        UnsafeVector<SecondaryCommandBuffer> attachedBuffers;

    public:
        virtual ~PrimaryCommandBuffer_(void) = default;
        void attachSecondary(const SecondaryCommandBuffer& buffer);

        static Pointer<PrimaryCommandBuffer_> create(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer);

    private:
        PrimaryCommandBuffer_(const Pointer<Device_>& device, const Pointer<CommandPool_>& pool, vk::CommandBuffer buffer);
    };

    typedef Pointer<PrimaryCommandBuffer_> PrimaryCommandBuffer;
}
#endif