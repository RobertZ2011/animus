#ifndef ANIMUS_FUTURE
#define ANIMUS_FUTURE

#include "types.hpp"
#include "Optional.hpp"
#include "AtomicObject.hpp"

namespace Animus {
    template<typename T>
    class Future : public AtomicObject {
        struct FutureData {
            Optional<T> value;
            Optional<Exception> exception;
        };

        Pointer<FutureData> data;
    private:

    public:
        Future(void) {

        }

        Future(const Future& future) {
            this->data = future.data;
        }

        ~Future(void) {

        }

        Future& operator=(const Future& future) {
            this->data = future.data;
            return *this;
        }

        void setValue(const T& value) {
            Lock lock(this);
            this->data->value = value;
        }

        void setException(const Exception& exception) {
            Lock lock(this);
            this->data->exception = exception;
        }

        T get(void) {
            this->wait();

            Lock lock(this);
            if(this->data->value.isSome) {
                return this->data->value.get();
            }
            else {
                throw this->data->exception.get();
            }
        }

        bool hasValue(void) {
            Lock lock(this);
            return this->data->value.isSome() || this->data->exception.isSome();
        }

        void wait(void) {
            while(!this->hasValue()) {
                //TODO: yield;
            }
        }
    };
}
#endif
