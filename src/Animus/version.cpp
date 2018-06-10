#include "version.hpp"

#include <sstream>

namespace Animus {
    bool operator>(const Version& lhs, const Version& rhs) {
        int majorLhs = std::get<0>(lhs);
        int minorLhs = std::get<1>(lhs);
        int versionLhs = std::get<2>(lhs);

        int majorRhs = std::get<0>(rhs);
        int minorRhs = std::get<1>(rhs);
        int versionRhs = std::get<2>(rhs);

        if(majorLhs > majorRhs) {
            return true;
        }
        else {
            if(minorLhs > minorRhs) {
                return true;
            }
            else {
                if(versionLhs > versionRhs) {
                    return true;
                }
            }
        }

        return false;
    }

    bool operator>=(const Version& lhs, const Version& rhs) {
        int majorLhs = std::get<0>(lhs);
        int minorLhs = std::get<1>(lhs);
        int versionLhs = std::get<2>(lhs);

        int majorRhs = std::get<0>(rhs);
        int minorRhs = std::get<1>(rhs);
        int versionRhs = std::get<2>(rhs);

        if(majorLhs >= majorRhs) {
            return true;
        }
        else {
            if(minorLhs >= minorRhs) {
                return true;
            }
            else {
                if(versionLhs >= versionRhs) {
                    return true;
                }
            }
        }

        return false;
    }

    template<>
    String toString<Version>(Version version) {
        std::stringstream stream;

        stream << std::get<0>(version) << '.' << std::get<1>(version) << '.' << std::get<2>(version);
        return stream.str();
    }
}
