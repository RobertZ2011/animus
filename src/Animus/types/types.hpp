#ifndef ANIMUS_TYPES
#define ANIMUS_TYPES

#include <functional>
#include <memory>
#include <tuple>
#include <exception>
#include <atomic>
#include <optional>
#include <unordered_map>

#include <glm/glm.hpp>

#include "../version.hpp"
#include "../macros/debug.hpp"
#include "../String.hpp"

namespace Animus {
    ANIMUS_REQUIRES_STD
    template<typename T>
    using Function = std::function<T>;

    ANIMUS_REQUIRES_STD
    template<typename T>
    using Pointer = std::shared_ptr<T>;

    ANIMUS_REQUIRES_STD
    template<typename T>
    using WeakPtr = std::weak_ptr<T>;

    ANIMUS_REQUIRES_STD
    template<typename... T>
    using Tuple = std::tuple<T...>;

    ANIMUS_REQUIRES_STD
    typedef std::exception Exception;

    ANIMUS_REQUIRES_STD
    template<typename K, typename V>
    using UnorderedMap = std::unordered_map<K, V>;

    ANIMUS_REQUIRES_STD
    template<typename T>
    using Atomic = std::atomic<T>;

    ANIMUS_REQUIRES_STD
    template<typename A, typename B>
    using Pair = std::pair<A, B>;

    ANIMUS_REQUIRES_STD
    template<typename T>
    using Optional = std::optional<T>;

    typedef glm::ivec2 Vec2i;
    typedef glm::vec2 Vec2f;
    ANIMUS_TODO("Add support for GLM quaternions")
    //typedef glm::gtc::quat Quat;
}

#endif
