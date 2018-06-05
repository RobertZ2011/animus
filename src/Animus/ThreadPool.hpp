#ifndef ANIMUS_THREAD_POOL
#define ANIMUS_THREAD_POOL

#include "types.hpp"
#include "Singleton.hpp"
#include "Queue.hpp"
#include "Vector.hpp"
#include "Future.hpp"
#include "macros.hpp"

#include <thread>

namespace Animus {
    REQUIRES_STD
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
        void queueWork(Queue<WorkItem>& queue);

        REQUIRES_STD
        static void sleep(unsigned int ms);

        REQUIRES_STD
        static void yield(void);

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

            this->dispatch([work, future]() mutable {
                try {
                    future.setValue(work());
                }
                catch(Exception &e) {
                    future.setException(e);
                }
            }, priority, false);

            return future;
        }

        template<typename T>
        Future<T> dispatchMainFuture(const Function<T(void)>& work) {
            Future<T> future;

            this->dispatchMain([work, future]() mutable {
                try {
                    future.setValue(work());
                }
                catch(Exception &e) {
                    future.setException(e);
                }
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
