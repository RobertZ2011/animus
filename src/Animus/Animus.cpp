#include "Animus.hpp"

namespace Animus {
    void init(void) {
        ThreadPool::init();
    }

    void deinit(void) {
        ThreadPool::deinit();
    }

    Version getVersion(void) {
        return Version(0, 0, 1);
    }
}
