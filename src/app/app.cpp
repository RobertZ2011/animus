#include <Animus/Animus.hpp>
#include "app.hpp"

#include <iostream>
#include <thread>
#include <chrono>

class App : public Animus::Application {
public:
    void init(void) override {
        Animus::ThreadPool::getSingleton().dispatchFuture<int>([]() {
            std::cout << "I'm a work item producing results" << std::endl;
            return 4 + 5;
        });
    }

    void deinit(void) override {

    }

    Animus::String getName(void) override {
        return "Test App";
    }

    Animus::Version getVersion(void) override {
        return Animus::Version(0, 0, 1);
    }

    Animus::Version getMinimumAnimusVersion(void) override {
        return Animus::getVersion();
    }
};


Animus::Application *create_animus_application(void) {
    return new App();
}

void destroy_animus_application(Animus::Application *app) {
    delete app;
}
