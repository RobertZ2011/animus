#ifndef ANIMUS_FILE_PATH
#define ANIMUS_FILE_PATH

#include "types.hpp"

namespace Animus {
    class FilePath {
        String path;

    public:
        FilePath(void);
        FilePath(const char *str);
        FilePath(const String& str);
        FilePath(const FilePath& path);
        String str(void) const;
        const char *c_str(void) const;
    };
}
#endif
