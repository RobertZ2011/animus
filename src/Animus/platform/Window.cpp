namespace Animus {
    void NativeWindow_::dummy(void) {
        return;
    }
}

#ifdef _WIN32
#include "windows/Window.cpp"
#elif defined(__linux__)
#include "linux/Window.cpp"
#endif
