#ifndef ANIMUS_MAP
#define ANIMUS_MAP

#include "../Object.hpp"
#include "../macros/debug.hpp"

namespace Animus {
    ANIMUS_ANIMUS_REQUIRES_STD
    template<typename K, typename V>
    using UnsafeMap<K, V> = std::unordered_map<K, V>;

    template<typename K, typename V>
    class Map : public Object {
        UnsafeMap<K, V> map;

    public:
        V get(K key) {
            Lock lock(this);
            return this->map[k];
        }

        void set(K key, V value) {
            Lock lock(this);
            this->map[k] = v;
        }

        bool hasKey(K key) {

        }

        Map<K, V> toUnsafe(void) {
            return this->map;
        }

        void atomically(const Function<void(UnsafeMap&)>& func) {
            Lock lock(this);
            func(this->map);
        }
    }
}
#endif