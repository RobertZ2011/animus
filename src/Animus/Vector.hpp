#ifndef ANIMUS_VECTOR
#define ANIMUS_VECTOR

#include "AtomicObject.hpp"
#include "macros.hpp"

#include <vector>
#include <initializer_list>

namespace Animus {
    REQUIRES_STD
    template<typename T>
    using UnsafeVector = std::vector<T>;

    template<typename T>
    class Vector : public AtomicObject {
    private:
        UnsafeVector<T> vector;

    public:
        Vector(void) {

        }

        Vector(Vector<T>&& vec) : AtomicObject(vec) {
            Lock lock(this);
            this->vector = std::move(vec.vector);
        }

        REQUIRES_STD
        Vector(const std::initializer_list<T>& list) {
            Lock lock(this);
            for(auto v: list) {
                this->vector.push_back(v);
            }
        }

        ~Vector(void) {

        }

        inline Vector<T>& operator=(Vector<T>&& vec) {
            AtomicObject::operator=(vec);
            this->vector = std::move(vec.vector);
        }

        inline void push_back(const T& value) {
            Lock lock(this);
            this->vector.push_back(value);
        }

        REQUIRES_STD
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
