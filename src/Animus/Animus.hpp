#ifndef ANIMUS_HEADER
#define ANIMUS_HEADER

#include "Application.hpp"
#include "Mutex.hpp"
#include "Lock.hpp"
#include "types/Queue.hpp"
#include "types/Vector.hpp"
#include "SharedObject.hpp"
#include "ThreadPool.hpp"
#include "types/types.hpp"
#include "System.hpp"
#include "Backend.hpp"
#include "Window.hpp"
#include "FilePath.hpp"
#include "Directory.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "Backend.hpp"

namespace Animus {
    void init(void);
    void deinit(void);

    FilePath getEngineBase(void);
}
#endif
