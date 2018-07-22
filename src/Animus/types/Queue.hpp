#ifndef ANIMUS_QUEUE
#define ANIMUS_QUEUE

#include "../Mutex.hpp"
#include "../Lock.hpp"
#include "types.hpp"
#include "../macros/debug.hpp"

#include <queue>

namespace Animus {
    ANIMUS_REQUIRES_STD
    template<typename T>
    using UnsafeQueue = std::queue<T>;

    template<typename T>
    class Queue {
    private:
        UnsafeQueue<T> queue;
        Mutex lock;

    public:
        Queue(void) {

        }

        ~Queue(void) {

        }

        inline bool empty(void) {
            Lock lock(this->lock);
            return this->queue.empty();
        }

        inline void pop(void) {
            Lock lock(this->lock);
            return this->queue.pop();
        }

        inline void push(const T& value) {
            Lock lock(this->lock);
            this->queue.push(value);
        }

        inline void push(T&& value) {
            Lock lock(this->lock);
            this->queue.push(std::forward<T>(value));
        }

        inline T& front(void) {
            Lock lock(this->lock);
            return this->queue.front();
        }

        inline T& pop_front(void) {
            Lock lock(this->lock);
            T& value = this->queue.front();
            this->queue.pop();
            return value;
        }

        inline Optional<T> pop_front_optional(void) {
            Lock lock(this->lock);

            if(this->queue.empty()) {
                return Optional<T>();
            }
            else {
                T item = this->queue.front();
                this->queue.pop();
                return Optional<T>(item);
            }
        }

        inline size_t size(void) {
            return this->queue.size();
        }

        inline void atomically(const Function<void(UnsafeQueue<T>&)>& func) {
            Lock lock(this->lock);
            func(this->queue);
        }
    };
}
#endif
