#ifndef ANIMUS_SYSTEM
#define ANIMUS_SYSTEM

#include "types/types.hpp"

namespace Animus {
    class System {
    public:
        ANIMUS_REQUIRES_STD
        [[noreturn]] static void fail(const char *message);
        
        [[noreturn]] static void fail(const String& message);
        [[noreturn]] static void fail(const Exception& message);
    };
}
#endif
