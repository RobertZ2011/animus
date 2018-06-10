#include "Future.hpp"

namespace Animus {
    Future<void>::Future(void) {
        this->data = Pointer<Future<void>::FutureData>(new Future<void>::FutureData());
    }

    Future<void>::Future(const Future<void>& future) {
        this->data = future.data;
    }

    Future<void>& Future<void>::operator=(const Future<void>& future) {
        this->data = future.data;
        return *this;
    }

    void Future<void>::setException(const Exception& exception) {
        this->data->exception = exception;
    }

    void Future<void>::setValue(void) {
        this->data->complete = true;
    }

    void Future<void>::get(void) {
        if(this->data->exception.has_value()) {
            throw this->data->exception.value();
        }
        else {
            this->wait();
        }
    }

    bool Future<void>::hasValue(void) {
        return this->data->complete;
    }

    void Future<void>::wait(void) {
        while(!this->data->complete) {
            ThreadPool::yield();
        }
    }
};
