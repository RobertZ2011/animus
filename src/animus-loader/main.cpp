#include <Animus/Animus.hpp>
#include <iostream>

typedef Animus::Application*(createAppType)(void);
typedef void(destroyAppType)(Animus::Application*);

int main(int argc, char **argv) {
    using namespace Animus;
    try {
        init();

        auto sharedObject = SharedObject_::create("libapp.so");
        auto createApp = sharedObject->loadFunction<createAppType>("create_animus_application");
        auto destroyApp = sharedObject->loadFunction<destroyAppType>("destroy_animus_application");

        Application *app = createApp();
        app->init();

        ThreadPool::getSingleton().mainLoop();

        app->deinit();
        destroyApp(app);

        deinit();
    }
    catch(Animus::Exception& e) {
        std::cerr << "Uncaught exception: " << e.what() << std::endl;
    }
    return 0;
}
