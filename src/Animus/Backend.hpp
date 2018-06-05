#ifndef ANIMUS_BACKEND
#define ANIMUS_BACKEND

#include "types.hpp"
#include "version.hpp"
#include "Vector.hpp"
#include "Singleton.hpp"
#include "SharedObject.hpp"
#include "GraphicsInterface.hpp"
#include "ComputeInterface.hpp"
#include "Optional.hpp"

namespace Animus {
    struct ComputeInterfaceInfo {
        const String name;
        const Version version;

        ComputeInterfaceInfo(const String& name, Version version);
        ~ComputeInterfaceInfo(void) = default;
    };

    struct GraphicsInterfaceInfo {
        const String name;
        const Version version;

        GraphicsInterfaceInfo(const String& name, Version version);
        ~GraphicsInterfaceInfo(void) = default;
    };

    class Window_;

    class Backend {
    public:
        virtual ~Backend(void) = default;

        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;

        virtual void init(void) = 0;
        virtual void deinit(void) = 0;

        virtual const UnsafeVector<GraphicsInterfaceInfo>& getGraphicsInterfaces(void) = 0;
        virtual const UnsafeVector<ComputeInterfaceInfo>& getComputeInterfaces(void) = 0;

        virtual GraphicsInterface createGraphicsInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) = 0;
        virtual ComputeInterface createComputeInterface(const Pointer<Window_>& window, const String& name, Optional<Version> version) = 0;
    };

    typedef Backend *(BackendCreateType)(void);
    typedef void (BackendDestroyType)(Backend *backend);

    class BackendManager : public Singleton<BackendManager> {
        UnsafeVector<Backend*> backends;
        UnsafeVector<SharedObject> objects;

        BackendManager(void);

    public:
        ~BackendManager(void);

        const UnsafeVector<Backend*>& getBackends(void);

        Backend *getDefaultBackend(void);

        static void init(void);
        static void deinit(void);
    };
}
#endif
