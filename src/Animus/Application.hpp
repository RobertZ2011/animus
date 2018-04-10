#ifndef ANIMUS_APPLICATION
#define ANIMUS_APPLICATION

#include "types.hpp"

namespace Animus {
    class Application {
    public:
        virtual ~Application(void) = default;

        virtual void init(void) = 0;
        virtual void deinit(void) = 0;

        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;
        virtual Version getMinimumAnimusVersion(void) = 0;
    };
}

#endif
