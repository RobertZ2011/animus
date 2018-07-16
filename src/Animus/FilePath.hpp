#ifndef ANIMUS_FILE_PATH
#define ANIMUS_FILE_PATH

#include "types/types.hpp"

#include <exception>

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

        FilePath operator+(const FilePath& path);
        FilePath operator+(const char *path);
        FilePath operator+(const String& path);

        bool exists(void) const;
        bool isFile(void) const;
        bool isDirectory(void) const;
    };

    template<>
    String toString(FilePath path);
}
#endif
