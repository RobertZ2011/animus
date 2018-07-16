#ifndef ANIMUS_SHARED_OBJECT
#define ANIMUS_SHARED_OBJECT

#include "types/types.hpp"
#include "FilePath.hpp"

#include <iostream>

namespace Animus {
    class SharedObject_;
    typedef Pointer<SharedObject_> SharedObject;

    template<typename Sig>
    class SharedFunction;

    template<typename R, typename... ARGS>
    class SharedFunction<R(ARGS...)> {
    private:
        Function<R(ARGS...)> func;
        SharedObject so;

    public:
        SharedFunction(void *ptr, const SharedObject& so) {
            this->so = so;
            this->func = reinterpret_cast<R(*)(ARGS...)>(ptr);
        }

        SharedFunction(void) {
        }

        ~SharedFunction(void) {

        }

        void destroy(void) {
            this->so = nullptr;
        }

        inline R operator()(ARGS... args) const {
            return this->func(args...);
        }

        inline explicit operator bool(void) const {
            return !!this->func;
        }
    };

    class SharedObject_ {
    private:
        void *so;
        WeakPtr<SharedObject_> self;

        SharedObject_(const FilePath&);

    public:
        class CannotOpen : public Exception {
        private:
            String message;
        public:
            CannotOpen(const FilePath& path) {
                this->message = String("Cannot load shared library: ") + path.str();
            }

            ~CannotOpen(void) = default;

            const char  *what(void) const noexcept override {
                return this->message.c_str();
            }
        };

        class NoFunction : public Exception {
        private:
            String message;
        public:
            NoFunction(const String& function) {
                this->message = String("Cannot load shared object function: ") + function;
            }

            ~NoFunction(void) = default;

            const char *what(void) const noexcept override {
                return this->message.c_str();
            }
        };

        ~SharedObject_(void);

        template<typename T>
        SharedFunction<T> loadFunction(const String& name) {
            return SharedFunction<T>(this->loadSymbol(name), this->self.lock());
        }

        void *loadSymbol(const String& name);

        static SharedObject create(const FilePath&);
    };

}
#endif
