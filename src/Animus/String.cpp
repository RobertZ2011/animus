#include "String.hpp"

#include <sstream>

namespace Animus {
    template<>
    String toString<String>(String str) {
        return str;
    }

    template<>
    String toString<char*>(char *str) {
        return String(str);
    }

    template<>
    String toString<const char*>(const char *str) {
        return String(str);
    }

    template<>
    String toString<unsigned int>(unsigned int value) {
        std::stringstream s;

        s << value;
        return s.str();
    }

    template<>
    String toString<int>(int value) {
        std::stringstream s;

        s << value;
        return s.str();
    }

    template<>
    String toString<unsigned long>(unsigned long value) {
        std::stringstream s;

        s << value;
        return s.str();
    }

    template<>
    String toString<long>(long value) {
        std::stringstream s;

        s << value;
        return s.str();
    }
}
