#include "Backend.hpp"

namespace Animus {
    BackendManager::BackendManager(void) {

    }

    BackendManager::~BackendManager(void) {
        
    }

    const Vector<Backend*>& BackendManager::getBackends(void) {
        return this->backends;
    }

    void BackendManager::init(void) {
        BackendManager::initSingleton(new BackendManager());
    }

    void BackendManager::deinit(void) {
        BackendManager::deinitSingleton();
    }
}
