#ifndef ANIMUS_ATOMIC
#define ANIMUS_ATOMIC

#include "types.hpp"
#include <mutex>

namespace Animus {
    class AtomicObject {
    private:
        std::mutex mutex;

    public:
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
