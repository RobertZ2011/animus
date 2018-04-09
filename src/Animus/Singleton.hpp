#ifndef ANIMUS_SINGLETON
#define ANIMUS_SINGLETON

#include "types.hpp"

#define ANIMUS_DEFINE_SINGLETON(t) template<> t *Singleton<t>::singleton = nullptr;

namespace Animus {
    template<class T>
    class Singleton {
    private:
        static T* singleton;

    public:
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
}
#endif
