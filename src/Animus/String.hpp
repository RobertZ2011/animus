#ifndef ANIMUS_STRING
#define ANIMUS_STRING

#include <string>
#include "macros/debug.hpp"

namespace Animus {
    ANIMUS_REQUIRES_STD
    typedef std::string String;

    template<typename T>
    String toString(T);

    template<>
    String toString<String>(String str);

    template<>
    String toString<char*>(char *str);

    template<>
    String toString<const char*>(const char *str);

    ANIMUS_REQUIRES_STD
    template<>
    String toString<unsigned int>(unsigned int value);

    ANIMUS_REQUIRES_STD
    template<>
    String toString<int>(int value);

    ANIMUS_REQUIRES_STD
    template<>
    String toString<unsigned long>(unsigned long value);

    ANIMUS_REQUIRES_STD
    template<>
    String toString<long>(long value);
}
#endif
