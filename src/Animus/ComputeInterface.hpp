#ifndef ANIMUS_COMPUTE_INTERFACE
#define ANIMUS_COMPUTE_INTERFACE

#include "types/types.hpp"
#include "version.hpp"

namespace Animus {
    class ComputeInterface_;
    typedef Pointer<ComputeInterface_> ComputeInterface;

    class ComputeInterface_ {
    public:
        virtual ~ComputeInterface_(void) = default;

        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;
    };
}

#endif
