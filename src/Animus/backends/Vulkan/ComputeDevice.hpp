#ifndef ANIMUS_COMPUTE_DEVICE
#define ANIMUS_COMPUTE_DEVICE

#include "../../Object.hpp"
#include "../../ComputeInterface.hpp"

#include "Device.hpp"

namespace Animus::Vulkan {
    class ComputeDevice : public Device, public ComputeInterface_, virtual public Object {

    protected:
        //useful for shared devices
        ComputeDevice(void) = default;
    };
}

#endif