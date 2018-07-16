#ifndef ANIMUS_FILE
#define ANIMUS_FILE

#include "FilePath.hpp"

#include <fstream>

namespace Animus {
    class File {
        ANIMUS_REQUIRES_STD
        std::fstream file;

    public:
        enum class Mode: uint32_t {
            Read = 0x1,
            Write = 0x2,
            Append = 0x4,
            Truncate = 0x8
        };

        File(const FilePath& path, Mode mode);
        File(void) = default;
        ~File(void);

        void open(const FilePath& path, Mode mode);
        void close(void);

        bool isOpen(void);
        void flush(void);

        void write(const String& str);

    private:
        static std::ios_base::openmode convertMode(Mode mode);
    };

    bool operator&(File::Mode lhs, File::Mode rhs);
    File::Mode operator|(File::Mode lhs, File::Mode rhs);
}
#endif
