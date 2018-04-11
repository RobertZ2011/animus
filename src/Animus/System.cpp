#include "System.hpp"
#include "ThreadPool.hpp"
#include "Animus.hpp"

#include <SDL2/SDL.h>
#include <cstdlib>

namespace Animus {
    void System::fail(const char *message) {
        ThreadPool::getSingleton().shutdown();

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Engine failure", message, NULL);
        deinit();
        std::exit(1);
    }

    void System::fail(const String& message) {
        System::fail(message.c_str());
    }

    void System::fail(const Exception& e) {
        String message = String("Failed with exception: ") + String(e.what());
        System::fail(message.c_str());
    }
}
