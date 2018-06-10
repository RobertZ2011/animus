#ifndef ANIMUS_FUTURE
#define ANIMUS_FUTURE

#include "types.hpp"
#include "macros.hpp"
#include "ThreadPool.hpp"

namespace Animus {

    template<typename T>
    class Future {
        struct FutureData {
            Optional<T> value;
            Optional<Exception> exception;
        };

        Pointer<FutureData> data;

    public:
        Future(void) {
            this->data = Pointer<FutureData>(new FutureData());
        }

        Future(const Future& future) {
            this->data = future.data;
        }

        ~Future(void) = default;

        Future& operator=(const Future& future) {
            this->data = future.data;
            return *this;
        }

        void setValue(const T& value) {
            this->data->value = value;
        }

        void setException(const Exception& exception) {
            this->data->exception = exception;
        }

        T get(void) {
            this->wait();

            if(this->data->value.has_value()) {
                return this->data->value.value();
            }
            else {
                throw this->data->exception.value();
            }
        }

        bool hasValue(void) {
            return this->data->value.has_value() || this->data->exception.has_value();
        }

        void wait(void) {
            while(!this->hasValue()) {
                ThreadPool::yield();
            }
        }
    };

    template<>
    class Future<void>  {
        struct FutureData {
            bool complete = false;
            Optional<Exception> exception;
        };

        Pointer<FutureData> data;

    public:
        Future(void);
        Future(const Future& future);
        ~Future(void) = default;

        Future& operator=(const Future& future);
        void setException(const Exception& exception);
        void setValue(void);
        void get(void);
        bool hasValue(void);
        void wait(void);
    };
}
#endif
