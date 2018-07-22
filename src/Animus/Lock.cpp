#include "Lock.hpp"

namespace Animus {
    Lock::Lock(Mutex& mutex) : mutex(mutex) {
        this->mutex.lock();
    }

    Lock::~Lock(void) {
        this->mutex.unlock();
    } 
}