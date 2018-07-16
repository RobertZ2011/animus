#ifndef ANIMUS_SINGLETON
#define ANIMUS_SINGLETON

#include "types/types.hpp"

namespace Animus {
    template<class T>
    class Singleton {
    private:
        static T *singleton;

    public:
        virtual ~Singleton() = default;

        static T& getSingleton(void) {
            return *Singleton<T>::singleton;
        }

        static void initSingleton(T *singleton) {
            Singleton<T>::singleton = singleton;
        }

        static void deinitSingleton(void) {
            delete Singleton<T>::singleton;
        }
    };

    template<typename T>
    T *Singleton<T>::singleton = nullptr;
}
#endif
