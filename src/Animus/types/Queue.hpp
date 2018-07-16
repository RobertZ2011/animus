#ifndef ANIMUS_QUEUE
#define ANIMUS_QUEUE

#include "../Object.hpp"
#include "types.hpp"
#include "../macros/debug.hpp"

#include <queue>

namespace Animus {
    ANIMUS_REQUIRES_STD
    template<typename T>
    using UnsafeQueue = std::queue<T>;

    template<typename T>
    class Queue : public Object {
    private:
        UnsafeQueue<T> queue;

    public:
        Queue(void) {

        }

        ~Queue(void) {

        }

        inline bool empty(void) {
            Lock lock(this);
            return this->queue.empty();
        }

        inline void pop(void) {
            Lock lock(this);
            return this->queue.pop();
        }

        inline void push(const T& value) {
            Lock lock(this);
            this->queue.push(value);
        }

        inline void push(T&& value) {
            Lock lock(this);
            this->queue.push(std::forward<T>(value));
        }

        inline T& front(void) {
            Lock lock(this);
            return this->queue.front();
        }

        inline T& pop_front(void) {
            Lock lock(this);
            T& value = this->queue.front();
            this->queue.pop();
            return value;
        }

        inline Optional<T> pop_front_optional(void) {
            Lock lock(this);

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
            Lock lock(this);
            func(this->queue);
        }
    };
}
#endif
