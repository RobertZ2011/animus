#ifndef ANIMUS_MUTEX
#define ANIMUS_MUTEX

#include <mutex>
#include "macros/debug.hpp"

namespace Animus {
    class Mutex {
        ANIMUS_REQUIRES_STD
        std::mutex mutex;
        
    public:
        Mutex(void) = default;
        Mutex(const Mutex& other) = delete;
        ~Mutex(void) = default;

        Mutex& operator=(const Mutex& other) = delete;

        void lock(void);
        void unlock(void);
        bool tryLock(void);
    };
}
#endif