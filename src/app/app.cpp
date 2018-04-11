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
            std::cout << "I'm a work item waiting for results" << std::endl;

            Future<int> f = ThreadPool::getSingleton().dispatchFuture<int>([]() {
                std:: cout << "I'm a work item returning results" << std::endl;
                return 4 + 5;
            });

            int r = f.get();
            std::cout << "Got " << r << std::endl;
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
