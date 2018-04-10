#ifndef ANIMUS_OPTIONAL
#define ANIMUS_OPTIONAL

namespace Animus {
    template<typename T>
    class Optional {
    private:
        T value;
        bool some;
    public:
        Optional(void) {
            this->some = false;
        }

        Optional(const T& v) : value(v) {
            this->some = true;
        }

        Optional(T&& v) : value(v) {
            this->some = true;
        }

        Optional<T>& operator=(const Optional<T>& op) {
            this->value = op.value;
            this->some = op.some;
            return *this;
        }

        Optional<T>& operator=(const T& value) {
            this->value = value;
            this->some = true;
            return *this;
        }

        T& get(void) {
            return this->value;
        }

        bool isSome(void) {
            return this->some;
        }

        explicit operator bool(void) {
            return this->isSome();
        }
    };
}
#endif
