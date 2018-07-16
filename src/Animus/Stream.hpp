#ifndef ANIMUS_STREAM
#define ANIMUS_STREAM

#include "types/types.hpp"

namespace Animus {
    class Stream_ {
    public:
        virtual ~Stream_(void) = default;


    };

    typedef Pointer<Stream_> Stream;
}

#endif