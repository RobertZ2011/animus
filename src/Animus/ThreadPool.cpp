#include "ThreadPool.hpp"
#include "Log.hpp"

#include <SDL2/SDL.h>
#include <chrono>
#include <cstdlib>

#include <iostream>

namespace Animus {
    ThreadPool::ThreadPool(void) {
        Log::getSingleton().logStr("ThreadPool begin init");
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

        Log::getSingleton().logStr("ThreadPool initialized");
    }

    ThreadPool::~ThreadPool(void) {
        Log::getSingleton().logStr("ThreadPool deinit");
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

    void ThreadPool::queueWork(Queue<WorkItem>& queue) {
        //execute no more than the current number of items in the queue
        int maxItems = queue.size();
        for(int j = 0; j < maxItems; j++) {
            Optional<WorkItem> optional = queue.pop_front_optional();

            if(optional.isSome()) {
                WorkItem work = optional.get();
                work.work();

                //don't requeue an item if the pool has stopped running
                if(work.loop && this->running) {
                    queue.push(work);
                }
            }
            else {
                break;
            }
        }
    }

    void ThreadPool::yield(void) {
        std::this_thread::yield();
    }

    void ThreadPool::sleep(unsigned int ms) {
        std::this_thread::sleep_for(std::chrono::duration<unsigned int, std::milli>(ms));
    }

    void ThreadPool::threadLoop(void) {
        while(1) {
            for(int i = (int) ThreadPool::Priority::High; i < (int) ThreadPool::Priority::Low; i++) {
                this->queueWork(this->queues[i]);
            }

            if(!this->running) {
                //only exit if all work is done
                bool stop = true;
                for(int i = (int) ThreadPool::Priority::High; i < (int) ThreadPool::Priority::Low; i++) {
                    if(!this->queues[i].empty()) {
                        stop = false;
                    }
                }

                if(stop) {
                    break;
                }
            }

            ThreadPool::yield();
        }
    }

    void ThreadPool::shutdown(void) {
        Log::getSingleton().logStr("ThreadPool shutdown");
        this->running = false;
    }

    void ThreadPool::mainLoop(void) {
        while(1) {
            //execute no more than the current number of items in the queue before yielding
            int maxItems = this->mainQueue.size();
            for(int j = 0; j < maxItems; j++) {
                this->queueWork(this->mainQueue);
            }

            //exit the loop if the pool is shutdown and all work is done
            if(!this->running && this->mainQueue.empty()) {
                break;
            }

            ThreadPool::yield();
        }

        //Wait until all other threads are finished before continuing
        for(auto& thread : this->threads) {
            thread.join();
        }

        Log::getSingleton().logStr("Main loop complete");
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
