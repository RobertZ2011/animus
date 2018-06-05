#include "Directory.hpp"

#include <dirent.h>
#include <sys/stat.h>
#include <iostream>

namespace Animus {
    Directory::Directory(const FilePath& path) {
        this->path = path;
    }

    Vector<FilePath> Directory::listFiles(void) {
        auto children = this->listChildren();

        children.filterInPlace([](const FilePath& path) -> bool {
            return path.isFile();
        });

        return children;
    }

    Vector<FilePath> Directory::listDirectories(void) {
        auto children = this->listChildren();

        children.filterInPlace([](const FilePath& path) -> bool {
            return path.isDirectory();
        });

        return children;
    }

    Vector<FilePath> Directory::listChildren(void) {
        DIR *dir = opendir(this->path.c_str());
        dirent *ent;
        Vector<FilePath> children;

        while((ent = readdir(dir)) != nullptr) {
            if(ent->d_type == DT_DIR ||
               ent->d_type == DT_REG ||
               ent->d_type == DT_LNK) {
                   if(String(ent->d_name) != "." && String(ent->d_name) != "..") {
                       children.push_back(this->path + ent->d_name);
                   }
            }
        }

        closedir(dir);
        return children;
    }
}
