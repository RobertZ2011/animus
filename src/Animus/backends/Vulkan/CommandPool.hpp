#ifndef ANIMUS_VULKAN_COMMAND_POOL
#define ANIMUS_VULKAN_COMMAND_POOL

#include "../../Mutex.hpp"
#include "../../types/types.hpp"

#include "Device.hpp"

#include "functions.hpp"
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class PrimaryCommandBuffer_;
    class SecondaryCommandBuffer_;

    class CommandPool_ {
        Mutex mutex;
        WeakPtr<CommandPool_> self;
        Device device;
        vk::CommandPool pool;
    
    public:
        ~CommandPool_(void);

        Pointer<PrimaryCommandBuffer_> createPrimaryBuffer(void);
        Pointer<SecondaryCommandBuffer_> createSecondaryBuffer(void);
        static Pointer<CommandPool_> create(const Device& device, uint32_t family);

        vk::CommandPool getPool(void);
        void lock(void);
        void unlock(void);

    protected:
        CommandPool_(const Device& device, uint32_t family);
    };

    typedef Pointer<CommandPool_> CommandPool;
}
#endif