#ifndef ANIMUS_TYPES
#define ANIMUS_TYPES

#include <functional>
#include <string>
#include <memory>
#include <tuple>
#include <exception>
#include <atomic>

namespace Animus {
    typedef std::string String;

    template<typename T>
    using Function = std::function<T>;

    template<typename T>
    using Pointer = std::shared_ptr<T>;

    template<typename T>
    using WeakPtr = std::weak_ptr<T>;

    template<typename... T>
    using Tuple = std::tuple<T...>;

    typedef Tuple<int, int, int> Version;

    typedef std::exception Exception;

    template<typename T>
    using Atomic = std::atomic<T>;

    /*typedef glm::ivec2 Vec2i;
    typedef glm::vec2 Vec2f;
    typedef glm::gtc::quat Quat;*/
}

#endif
