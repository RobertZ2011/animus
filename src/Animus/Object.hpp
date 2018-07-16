#ifndef ANIMUS_ATOMIC
#define ANIMUS_ATOMIC

#include "types/types.hpp"
#include <mutex>

namespace Animus {
    class Object {
    private:
        ANIMUS_REQUIRES_STD
        std::mutex mutex;

    public:
        Object(void) = default;
        ~Object(void) = default;

        void lock(void);
        void unlock(void);
        bool trylock(void);
    };

    class Lock {
    private:
        Object *atomic;
    public:
        Lock(Object& atomic);
        Lock(Object *atomic);
        ~Lock();
    };
}

#endif
