#include <Animus/Animus.hpp>
#include "app.hpp"

#include <iostream>
#include <thread>
#include <chrono>

using namespace Animus;

class App : public Application {
public:
    void init(void) override {
        ThreadPool::getSingleton().dispatchMain([]() {
            auto window = Window_::create(Vec2i(640, 480), "Test");
            Backend *backend = BackendManager::getSingleton().getDefaultBackend();

            backend->init();

            std::cin.get();
            ThreadPool::getSingleton().shutdown();
        });
    }

    void deinit(void) override {

    }

    String getName(void) override {
        return "Test App";
    }

    Version getVersion(void) override {
        return Version(0, 0, 1);
    }

    Version getMinimumAnimusVersion(void) override {
        return getVersion();
    }
};


Application *create_animus_application(void) {
    return new App();
}

void destroy_animus_application(Application *app) {
    delete app;
}
