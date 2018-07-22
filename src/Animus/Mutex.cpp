#include "Mutex.hpp"

namespace Animus {
    void Mutex::lock(void) {
        this->mutex.lock();
    }

    void Mutex::unlock(void) {
        this->mutex.unlock();
    }

    bool Mutex::tryLock(void) {
        return this->mutex.try_lock();
    }
}