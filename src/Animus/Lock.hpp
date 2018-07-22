#ifndef ANIMUS_LOCK
#define ANIMUS_LOCK

#include "Mutex.hpp"

namespace Animus {
    /*template<typename T>
    class Lockable {
        Pointer<T> lockable;
    public:
        Lockable(const Pointer<T>& ptr) {
            this->lockable = ptr;
        }
    };*/

    class Lock {
        Mutex& mutex;
    public:
        Lock(Mutex& mutex);
        ~Lock(void);
    };
}

#endif