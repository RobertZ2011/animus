#include "Backend.hpp"
#include "Directory.hpp"
#include "SharedObject.hpp"
#include "Log.hpp"
#include "Error.hpp"

namespace Animus {
    ComputeInterfaceInfo::ComputeInterfaceInfo(const String& name, Version version) : name(name), version(version) {

    }

    GraphicsInterfaceInfo::GraphicsInterfaceInfo(const String& name, Version version) : name(name), version(version) {

    }

    BackendManager::BackendManager(void) {
        ANIMUS_TODO("Make this work with different paths")
        Directory backendDir = Directory("backends");
        auto backendFiles = backendDir.listChildren();

        Log::getSingleton().logStr("Locating backends");
        for(size_t i = 0; i < backendFiles.size(); i++) {
            Log::getSingleton().log("\tFound: %", backendFiles[i]);

            try {
                SharedObject object = SharedObject_::create(backendFiles[i]);
                auto createBackend = object->loadFunction<BackendCreateType>("create_backend");
                Backend *backend = createBackend();

                this->objects.push_back(object);
                this->backends.push_back(backend);
            }
            catch(Exception &e) {
                Log::getSingleton().error("\tFailed to load backend %, %", backendFiles[i], e);
            }
        }

        if(this->backends.size() == 0) {
            Log::getSingleton().fatalStr("Failed to find any backends");
        }

        Log::getSingleton().log("Found % backends", this->backends.size());

        for(Backend *backend: this->backends) {
            auto graphics = backend->getGraphicsInterfaces();
            auto compute = backend->getComputeInterfaces();

            Log::getSingleton().log("\t% %", backend->getName(), backend->getVersion());

            Log::getSingleton().logStr("\tGraphics");
            for(auto& interface: graphics) {
                Log::getSingleton().log("\t\t% %", interface.name, interface.version);
            }

            Log::getSingleton().logStr("\tCompute");
            for(auto& interface: compute) {
                Log::getSingleton().log("\t\t% %", interface.name, interface.version);
            }
        }
    }

    BackendManager::~BackendManager(void) {
        for(size_t i = 0; i < this->backends.size(); i++) {
            auto destroyBackend = this->objects[i]->loadFunction<BackendDestroyType>("destroy_backend");
            destroyBackend(this->backends[i]);
        }
    }

    const UnsafeVector<Backend*>& BackendManager::getBackends(void) {
        return this->backends;
    }

    Backend *BackendManager::getDefaultBackend(void) {
        for(Backend *backend: this->backends) {
            if(backend->getName() == "Vulkan") {
                return backend;
            }
        }

        //We're going to have atleast one backend, because not finding any is fatal
        return this->backends[0];
    }

    void BackendManager::init(void) {
        BackendManager::initSingleton(new BackendManager());
    }

    void BackendManager::deinit(void) {
        BackendManager::deinitSingleton();
    }
}
