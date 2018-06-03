#ifndef ANIMUS_BACKEND
#define ANIMUS_BACKEND

#include "types.hpp"
#include "version.hpp"
#include "Vector.hpp"
#include "Singleton.hpp"

namespace Animus {
    struct ComputeInterfaceInfo {
        const String name;
        const Version version;
    };

    struct GraphicsInterfaceInfo {
        const String name;
        const Version version;
    }

    class Window_;

    class Backend {
    public:
        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;

        virtual Vector<GraphicsInterfaceInfo> getGraphicsInterfaces(const Pointer<Window_>& window) = 0;
        virtual Vector<ComputeInterfaceInfo> getComputeInterfaces(const Pointer<Window_>& window) = 0;

        virtual GraphicsInterface createGraphicsInterface(const Pointer<Window_>& window, const GraphicsInterfaceInfo& info) = 0;
        virtual ComputeInterface createComputeInterface(const Pointer<Window_>& window, const ComputeInterfaceInfo& info) = 0;
    };

    typedef Backend (*BackendCreateType)(void);
    typedef void (*BackendDestroyType)(Backend *backend);

    class BackendManager : public Singleton<BackendManager> {
        Vector<Backend*> backends;
        Vector<SharedObject> objects;

    public:
        BackendManager(void);
        ~BackendManager(void);

        const Vector<Backend*>& getBackends(void);

        static void init(void);
        static void deinit(void);
    }:
}
#endif
