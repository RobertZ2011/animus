#ifndef ANIMUS_STRING
#define ANIMUS_STRING

#include <string>
#include "macros.hpp"

namespace Animus {
    REQUIRES_STD
    typedef std::string String;

    template<typename T>
    String toString(T);

    template<>
    String toString<String>(String);

    REQUIRES_STD
    template<>
    String toString<unsigned int>(unsigned int value);

    REQUIRES_STD
    template<>
    String toString<int>(int value);

    REQUIRES_STD
    template<>
    String toString<unsigned long>(unsigned long value);

    REQUIRES_STD
    template<>
    String toString<long>(long value);
}
#endif