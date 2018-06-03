#ifndef ANIMUS_VERSION
#define ANIMUS_VERSION

#include "macros.hpp"

#include <tuple>

namespace Animus {
    REQUIRES_STD
    typedef std::tuple<int, int, int> Version;

    REQUIRES_STD
    bool operator>(const Version& lhs, const Version& rhs);
}
#endif