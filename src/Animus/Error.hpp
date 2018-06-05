#ifndef ANIMUS_ERROR
#define ANIMUS_ERROR

#include <exception>

#include "types.hpp"
#include "macros.hpp"
#include "String.hpp"

namespace Animus {
    class FilePath;

    REQUIRES_STD
    typedef std::exception Exception;

    template<>
    String toString<Exception>(Exception e);

    class FilePermissionDenied : public Exception {
        String message;
    public:
        FilePermissionDenied(const FilePath& path);
        ~FilePermissionDenied(void) = default;

        const char *what(void) const noexcept override;
    };

    class FileNotExist : public Exception {
        String message;
    public:
        FileNotExist(const FilePath& path);
        ~FileNotExist(void) = default;

        const char *what(void) const noexcept override;
    };

    class FileUnknownError : public Exception {
        String message;
    public:
        FileUnknownError(const FilePath& path);
        ~FileUnknownError(void) = default;

        const char *what(void) const noexcept override;
    };

    class FileNotOpen : public Exception {
        String message;
    public:
        FileNotOpen(void) = default;
        ~FileNotOpen(void) = default;

        const char *what(void) const noexcept override;
    };
}
#endif
