#ifndef ANIMUS_VERSION
#define ANIMUS_VERSION

#include "macros/debug.hpp"
#include "String.hpp"

#include <tuple>

namespace Animus {
    ANIMUS_REQUIRES_STD
    typedef std::tuple<int, int, int> Version;

    ANIMUS_REQUIRES_STD
    bool operator>(const Version& lhs, const Version& rhs);

    bool operator>=(const Version& lhs, const Version& rhs);

    ANIMUS_REQUIRES_STD
    template<>
    String toString<Version>(Version version);

    Version getVersion(void);
}
#endif
