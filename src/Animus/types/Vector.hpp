#ifndef ANIMUS_VECTOR
#define ANIMUS_VECTOR

#include "../macros/debug.hpp"
#include "../Lock.hpp"
#include "types.hpp"

#include <vector>
#include <initializer_list>
#include <algorithm>

namespace Animus {
    ANIMUS_REQUIRES_STD
    template<typename T>
    using UnsafeVector = std::vector<T>;

    template<typename T>
    class Vector{
    private:
        UnsafeVector<T> vector;
        Mutex lock;

    public:
        Vector(void) {

        }

        Vector(const Vector<T>& vec) {
            Lock lock1(vec.lock);
            Lock lock2(this->lock);

            for(size_t i = 0; i < vec.size(); i++) {
                this->push_back(vec[i]);
            }
        }

        Vector(Vector<T>&& vec) {
            Lock lock(this->lock);
            this->vector = std::move(vec.vector);
        }

        ANIMUS_REQUIRES_STD
        Vector(const std::initializer_list<T>& list) {
            Lock lock(this->lock);
            for(auto v: list) {
                this->vector.push_back(v);
            }
        }

        ~Vector(void) {

        }

        inline Vector<T>& operator=(const std::initializer_list<T>& list) {
            Lock lock(this->lock);
            for(auto v: list) {
                this->vector.push_back(v);
            }
        }

        inline void push_back(const T& value) {
            Lock lock(this->lock);
            this->vector.push_back(value);
        }

        ANIMUS_REQUIRES_STD
        inline void push_back(T&& value) {
            Lock lock(this->lock);
            this->vector.push_back(std::forward<T>(value));
        }

        inline T& operator[](size_t index) {
            Lock lock(this->lock);
            return this->vector[index];
        }

        inline size_t size(void) {
            Lock lock(this->lock);
            return this->vector.size();
        }

        ANIMUS_REQUIRES_STD
        inline void filterInPlace(const Function<bool(const T&)>& func) {
            Lock lock(this->lock);
            this->vector.erase(std::remove_if(this->vector.begin(),
                this->vector.end(),
                func
            ));
        }

        UnsafeVector<T> toUnsafe(void) const {
            Lock lock(this->lock);
            return this->vector;
        }

        //allows a function to mutate the underlying vector with only one lock call
        inline void atomically(const Function<void(UnsafeVector<T>&)>& func) {
            Lock lock(this->lock);
            func(this->vector);
        }
    };
}
#endif
