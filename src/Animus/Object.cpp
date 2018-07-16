#include "Object.hpp"

namespace Animus {
    void Object::lock(void) {
        this->mutex.lock();
    }

    void Object::unlock(void) {
        this->mutex.unlock();
    }

    bool Object::trylock(void) {
        return this->mutex.try_lock();
    }

    Lock::Lock(Object& atomic) {
        atomic.lock();
        this->atomic = &atomic;
    }

    Lock::Lock(Object *atomic) {
        atomic->lock();
        this->atomic = atomic;
    }


    Lock::~Lock() {
        atomic->unlock();
    }
}
