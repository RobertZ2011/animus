#ifndef ANIMUS_ERROR
#define ANIMUS_ERROR

#include <exception>

#include "types/types.hpp"
#include "macros/debug.hpp"
#include "String.hpp"

namespace Animus {
    class FilePath;

    ANIMUS_REQUIRES_STD
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

    class RuntimeError : public Exception {
        String message;
    public:
        RuntimeError(const String& str);
        ~RuntimeError(void) = default;

        const char *what(void) const noexcept override;
    };
}
#endif
