#ifndef ANIMUS_TYPES
#define ANIMUS_TYPES

#include <functional>
#include <string>
#include <memory>
#include <tuple>
#include <exception>
#include <atomic>

#include <glm/glm.hpp>

#include "version.hpp"
#include "macros.hpp"

namespace Animus {
    REQUIRES_STD
    typedef std::string String;

    REQUIRES_STD
    template<typename T>
    using Function = std::function<T>;

    REQUIRES_STD
    template<typename T>
    using Pointer = std::shared_ptr<T>;

    REQUIRES_STD
    template<typename T>
    using WeakPtr = std::weak_ptr<T>;

    REQUIRES_STD
    template<typename... T>
    using Tuple = std::tuple<T...>;

    REQUIRES_STD
    typedef std::exception Exception;

    REQUIRES_STD
    template<typename T>
    using Atomic = std::atomic<T>;

    typedef glm::ivec2 Vec2i;
    typedef glm::vec2 Vec2f;
    TODO("Add support for GLM quaternions")
    //typedef glm::gtc::quat Quat;
}

#endif
