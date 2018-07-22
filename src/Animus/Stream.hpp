#ifndef ANIMUS_STREAM
#define ANIMUS_STREAM

#include "types/types.hpp"

namespace Animus {
    class Stream_ {
    public:
        virtual ~Stream_(void) = default;

        virtual void seek(void) = 0;
        virtual void tell(void) = 0;
        virtual void read(void) = 0;
    };

    typedef Pointer<Stream_> Stream;
}

#endif