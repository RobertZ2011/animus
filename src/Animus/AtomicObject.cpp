#include "AtomicObject.hpp"

namespace Animus {
    AtomicObject::AtomicObject(AtomicObject&& object) : mutex(std::move(object.mutex)) {
        
    }

    void AtomicObject::lock(void) {
        this->mutex.lock();
    }

    void AtomicObject::unlock(void) {
        this->mutex.unlock();
    }

    bool AtomicObject::trylock(void) {
        return this->mutex.try_lock();
    }

    Lock::Lock(AtomicObject& atomic) {
        atomic.lock();
        this->atomic = &atomic;
    }

    Lock::Lock(AtomicObject *atomic) {
        atomic->lock();
        this->atomic = atomic;
    }


    Lock::~Lock() {
        atomic->unlock();
    }
}
