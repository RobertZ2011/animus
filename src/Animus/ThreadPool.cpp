#include "ThreadPool.hpp"

#include <SDL2/SDL.h>

namespace Animus {
    ANIMUS_DEFINE_SINGLETON(ThreadPool);

    ThreadPool::ThreadPool(void) {
        //seems to give the number of logical processors, divide by 2 to get physical
        //subtract 1 for the main thread
        int numThreads = Thread::hardware_concurrency() / 2 - 1;
        numThreads = (numThreads <= 0) ? 1 : numThreads; //make sure we have at least one thread

        this->running = true;
        for(int i = 0; i < numThreads; i++) {
            this->threads.push_back(Thread([this] {
                this->threadLoop();
            }));
        }
    }

    ThreadPool::~ThreadPool(void) {

    }

    void ThreadPool::dispatch(const Function<void(void)>& work, ThreadPool::Priority priority, bool loop) {
        ThreadPool::WorkItem item;

        if(!this->running) {
            throw ThreadPool::NotRunning();
        }

        item.work = work;
        item.loop = loop;

        this->queues[(int) priority].push(item);
    }

    void ThreadPool::dispatchMain(const Function<void(void)>& work, bool loop) {
        ThreadPool::WorkItem item;

        if(!this->running) {
            throw ThreadPool::NotRunning();
        }

        item.work = work;
        item.loop = loop;

        this->mainQueue.push(item);
    }

    void ThreadPool::threadLoop(void) {
        while(this->running) {
            for(int i = (int) ThreadPool::Priority::High; i < (int) ThreadPool::Priority::Low; i++) {
                if(!this->queues[i].empty()) {
                    WorkItem item = this->queues[i].pop_front();

                    item.work();
                }
                //for each queue, execute no more than the current number of items in the queue
                //then move to the next queue
                /*int maxItems = this->queues[i].size();
                for(int j = 0; j < maxItems; j++) {
                    Optional<WorkItem> optional = this->queues[i].pop_front_optional();

                    if(optional.isSome()) {
                        WorkItem work(optional.get());
                        work.work();

                        if(work.loop) {
                            this->queues[i].push(work);
                        }
                    }
                    else {
                        break;
                    }
                }*/
            }

            //TODO: yield here
        }
    }

    void ThreadPool::shutdown(void) {
        //if we're not running then the pool has already been shutdown
        if(!this->running) {
            return;
        }

        this->running = false;

        for(auto& thread : this->threads) {
            thread.join();
        }
    }

    void ThreadPool::mainLoop(void) {
        while(this->running) {
            //execute no more than the current number of items in the queue before yielding
            int maxItems = this->mainQueue.size();
            for(int j = 0; j < maxItems; j++) {
                Optional<WorkItem> optional(this->mainQueue.pop_front_optional());

                if(optional.isSome()) {
                    WorkItem work = optional.get();
                    work.work();

                    if(work.loop) {
                        this->mainQueue.push(work);
                    }
                }
                else {
                    break;
                }
            }

            //TODO: yield here
        }
    }

    void ThreadPool::init(void) {
        Singleton<ThreadPool>::initSingleton(new ThreadPool());
    }

    void ThreadPool::deinit(void) {
        Singleton<ThreadPool>::deinitSingleton();
    }

    ThreadPool::WorkItem::WorkItem(void) {
        this->loop = false;
    }

    ThreadPool::WorkItem::WorkItem(const WorkItem& item) {
        this->work = item.work;
        this->loop = item.loop;
    }

    ThreadPool::WorkItem::~WorkItem(void) {

    }

    ThreadPool::WorkItem& ThreadPool::WorkItem::operator=(const WorkItem& item) {
        this->work = item.work;
        this->loop = item.loop;
        return *this;
    }
}
