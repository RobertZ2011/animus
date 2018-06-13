#include <SDL2/SDL_syswm.h>

namespace Animus {
    struct NativeWindow_ {
        virtual ~NativeWindow_(void) = default;
        virtual void dummy(void);
    };

    typedef Pointer<NativeWindow_> NativeWindow;
}

#ifdef _WIN32
#include "windows/Window.hpp"
#elif defined(__linux__)
#include "linux/Window.hpp"
#endif
