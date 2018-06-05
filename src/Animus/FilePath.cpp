#include "FilePath.hpp"
#include "Error.hpp"

#include <sys/stat.h>
#include <errno.h>

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

    FilePath FilePath::operator+(const FilePath& path) {
        return FilePath(this->path + "/" + path.str());
    }

    FilePath FilePath::operator+(const char *path) {
        return FilePath(this->path + "/" + String(path));
    }

    FilePath FilePath::operator+(const String& path) {
        return FilePath(this->path + "/" + path);
    }

    bool FilePath::exists(void) const {
        struct stat s;
        int err = stat(this->path.c_str(), &s);

        if(err == 0) {
            return true;
        }
        else
        if(err == ENOENT) {
            return false;
        }
        else
        if(err == EACCES){
            throw FilePermissionDenied(*this);
        }
        else {
            throw FileUnknownError(*this);
        }
    }

    bool FilePath::isFile(void) const {
        if(!this->exists()) {
            throw FileNotExist(*this);
        }
        else {
            struct stat s;
            int err = stat(this->path.c_str(), &s);

            if(err != 0) {
                if(err == EACCES) {
                    throw FilePermissionDenied(*this);
                }
                else {
                    throw FileUnknownError(*this);
                }
            }

            return S_ISREG(s.st_mode);
        }
    }

    bool FilePath::isDirectory(void) const {
        if(!this->exists()) {
            throw FileNotExist(*this);
        }
        else {
            struct stat s;
            int err = stat(this->path.c_str(), &s);

            if(err != 0) {
                if(err == EACCES) {
                    throw FilePermissionDenied(*this);
                }
                else {
                    throw FileUnknownError(*this);
                }
            }

            return S_ISDIR(s.st_mode);
        }
    }

    template<>
    String toString(FilePath path) {
        return path.str();
    }
}
