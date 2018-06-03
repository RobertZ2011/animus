#ifndef ANIMUS_ATOMIC
#define ANIMUS_ATOMIC

#include "types.hpp"
#include <mutex>

namespace Animus {
    class AtomicObject {
    private:
        REQUIRES_STD
        std::mutex mutex;

    public:
        AtomicObject(AtomicObject&& object);
        AtomicObject(void) = default;
        ~AtomicObject(void) = default;

        void lock(void);
        void unlock(void);
        bool trylock(void);
    };

    class Lock {
    private:
        AtomicObject *atomic;
    public:
        Lock(AtomicObject& atomic);
        Lock(AtomicObject *atomic);
        ~Lock();
    };
}

#endif
