#ifndef ANIMUS_VECTOR
#define ANIMUS_VECTOR

#include "AtomicObject.hpp"

#include <vector>

namespace Animus {
    template<typename T>
    using UnsafeVector = std::vector<T>;

    template<typename T>
    class Vector : public AtomicObject {
    private:
        UnsafeVector<T> vector;

    public:
        Vector(void) {

        }

        ~Vector(void) {

        }

        inline void push_back(const T& value) {
            Lock lock(this);
            this->vector.push_back(value);
        }

        inline void push_back(T&& value) {
            Lock lock(this);
            this->vector.push_back(std::forward<T>(value));
        }

        inline T& operator[](size_t index) {
            Lock lock(this);
            return this->vector[index];
        }

        //allows a function to mutate the underlying vector with only one lock call
        inline void atomically(const Function<void(UnsafeVector<T>&)>& func) {
            Lock lock(this);
            func(this->vector);
        }
    };
}
#endif
