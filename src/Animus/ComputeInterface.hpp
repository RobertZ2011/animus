#ifndef ANIMUS_COMPUTE_INTERFACE
#define ANIMUS_COMPUTE_INTERFACE

#include "types.hpp"
#include "version.hpp"

namespace Animus {
    class _ComputeInterface;
    typedef Pointer<_ComputeInterface> ComputeInterface;

    class _ComputeInterface {
    public:
        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;
    };
}

#endif
