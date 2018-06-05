#include "File.hpp"
#include "Error.hpp"

namespace Animus {
    File::File(const FilePath& path, Mode mode) {
        this->open(path, mode);
    }

    File::~File(void) {
        if(this->isOpen()) {
            this->close();
        }
    }

    void File::open(const FilePath& path, Mode mode) {
        this->file.open(path.c_str(), File::convertMode(mode));
    }

    void File::close(void) {
        this->file.close();
    }

    bool File::isOpen(void) {
        return this->file.is_open();
    }

    void File::flush(void) {
        this->file.flush();
    }

    void File::write(const String& str) {
        if(!this->isOpen()) {
            throw FileNotOpen();
        }

        this->file << str;
    }

    std::ios_base::openmode File::convertMode(Mode mode) {
        std::ios_base::openmode m = std::fstream::binary;

        if(mode & File::Mode::Write) {
            m |= std::fstream::out;
        }

        if(mode & File::Mode::Read) {
            m |= std::fstream::in;
        }

        if(mode & File::Mode::Append) {
            m |= std::fstream::app;
        }

        if(mode & File::Mode::Truncate) {
            m |= std::fstream::trunc;
        }

        return m;
    }

    bool operator&(File::Mode lhs, File::Mode rhs) {
        auto l = static_cast<uint32_t>(lhs);
        auto r = static_cast<uint32_t>(rhs);

        return (bool)(l & r);
    }

    File::Mode operator|(File::Mode lhs, File::Mode rhs) {
        auto l = static_cast<uint32_t>(lhs);
        auto r = static_cast<uint32_t>(rhs);

        return static_cast<File::Mode>(l | r);
    }
}
