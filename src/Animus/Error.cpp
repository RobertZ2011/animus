#include "Error.hpp"
#include "FilePath.hpp"

namespace Animus {
    template<>
    String toString<Exception>(Exception e) {
        return String(e.what());
    }

    FilePermissionDenied::FilePermissionDenied(const FilePath& path) {
        this->message = String("Cannot access ") + path.str() + String(", permission denied");
    }

    const char *FilePermissionDenied::what(void) const noexcept {
        return this->message.c_str();
    }

    FileNotExist::FileNotExist(const FilePath& path) {
        this->message = String("File: ") + path.str() + String(" does not exist");
    }

    const char *FileNotExist::what(void) const noexcept {
        return this->message.c_str();
    }

    FileUnknownError::FileUnknownError(const FilePath& path){
        this->message = String("File: ") + path.str() + String(" encountered unknown error");
    }

    const char *FileUnknownError::what(void) const noexcept {
        return this->message.c_str();
    }

    const char *FileNotOpen::what(void) const noexcept {
        return "Filesystem object not open";
    }
}
