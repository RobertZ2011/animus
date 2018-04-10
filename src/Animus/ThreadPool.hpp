#ifndef ANIMUS_THREAD_POOL
#define ANIMUS_THREAD_POOL

#include "types.hpp"
#include "Singleton.hpp"
#include "Queue.hpp"
#include "Vector.hpp"
#include "Future.hpp"

#include <thread>
#include <iostream>

namespace Animus {
    typedef std::thread Thread;

    class ThreadPool : public Singleton<ThreadPool> {
    private:
        struct WorkItem;

        UnsafeVector<Thread> threads;
        Queue<WorkItem> queues[3];
        Queue<WorkItem> mainQueue;
        Atomic<bool> running;

        ThreadPool(void);
        void threadLoop(void);

    public:
        enum class Priority {
            Low = 2,
            Medium = 1,
            High = 0,
            Default = Medium,
        };

        class NotRunning : public Exception {

        };

        ~ThreadPool(void);

        void dispatch(const Function<void(void)>& work, Priority priority = Priority::Default, bool loop = false);
        void dispatchMain(const Function<void(void)>& function, bool loop = false);

        template<typename T>
        Future<T> dispatchFuture(const Function<T(void)>& work, Priority priority = Priority::Default) {
            Future<T> future;

            std::cout << !!work << std::endl;
            this->dispatch([work, future]() mutable {
                std::cout << !!work << std::endl;
                future.setValue(work());
            }, priority, false);

            return future;
        }

        template<typename T>
        Future<T> dispatchMainFuture(const Function<T(void)>& work) {
            Future<T> future;

            this->dispatchMain([work, future]() mutable {
                future.setValue(work());
            }, false);

            return future;
        }

        void shutdown(void);

        void mainLoop(void);

        static void init(void);
        static void deinit(void);

    private:
        struct WorkItem {
            bool loop;
            Function<void(void)> work;

            WorkItem(void);
            WorkItem(const WorkItem& item);
            ~WorkItem(void);
            WorkItem& operator=(const WorkItem& item);
        };
    };
}
#endif
