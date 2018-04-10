#ifndef ANIMUS_SHARED_OBJECT
#define ANIMUS_SHARED_OBJECT

#include "types.hpp"
#include "FilePath.hpp"

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

        ~SharedFunction(void) {

        }

        R operator()(ARGS... args) const {
            return this->func(args...);
        }

        explicit operator bool(void) const {
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
            FilePath path;
        public:
            CannotOpen(const FilePath& path) {
                this->path = path;
            }

            ~CannotOpen(void) {

            }

            const char  *what(void) const noexcept override {
                return "Cannot load shared library";
            }
        };

        class NoFunction : public Exception {
        private:
            String function;
        public:
            NoFunction(const String& function) {
                this->function = function;
            }

            ~NoFunction(void) {

            }

            const char * what(void) const noexcept override {
                return "Cannot load shared object function";
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
