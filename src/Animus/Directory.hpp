#ifndef ANIMUS_DIRECTORY
#define ANIMUS_DIRECTORY

#include "FilePath.hpp"
#include "File.hpp"
#include "types/Vector.hpp"

namespace Animus {
    class Directory {
        FilePath path;
    public:
        Directory(const FilePath& path);
        ~Directory(void) = default;

        Vector<FilePath> listFiles(void);
        Vector<FilePath> listDirectories(void);
        Vector<FilePath> listChildren(void);

        static void create(const FilePath& path);
    };
}

#endif
