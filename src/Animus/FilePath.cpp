#include "FilePath.hpp"

namespace Animus {
    FilePath::FilePath(void) {
        this->path = "";
    }

    FilePath::FilePath(const char *str) {
        this->path = str;
    }

    FilePath::FilePath(const String& str) {
        this->path = str;
    }

    FilePath::FilePath(const FilePath& path) {
        this->path = path.str();
    }

    String FilePath::str(void) const {
        return this->path;
    }

    const char *FilePath::c_str(void) const {
        return this->path.c_str();
    }
}
