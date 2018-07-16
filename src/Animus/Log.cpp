#include "Log.hpp"

#include <chrono>
#include <sstream>
#include <iostream>

namespace Animus {
    Log::Log(void) {
        this->file.open("logfile", File::Mode::Write);
        this->logStr("Log opened");
    }

    Log::~Log(void) {
        this->logStr("Log closed");
    }

    String Log::logRaw(Log::Level level, const String& fmt, const UnsafeVector<String>& args) {
        std::stringstream stream;
        int argCount = 0;
        auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());

        stream << '[' << now.time_since_epoch().count() << ']' << '[' << toString<Log::Level>(level) << ']';

        for(size_t i = 0; i < fmt.length(); i++) {
            if(fmt[i] == '%') {
                //see if this is an escaped %
                if(i + 1 < fmt.length()) {
                    if(fmt[i + 1] == '%') {
                        stream << '%';
                        continue;
                    }
                }

                if(argCount >= args.size()) {
                    stream << "<argument exceeds range>";
                }
                else {
                    stream << args[argCount];
                }

                argCount++;
            }
            else {
                stream << fmt[i];
            }
        }

        stream << std::endl;

        //Lock lock(this);
        //this->file.write(stream.str());
        std::cout << stream.str();
        return stream.str();
    }

    void Log::logStr(const String& str) {
        UnsafeVector<String> none;
        this->logRaw(Log::Level::Log, str, none);
    }

    void Log::warnStr(const String& str) {
        UnsafeVector<String> none;
        this->logRaw(Log::Level::Warning, str, none);
    }

    void Log::errorStr(const String& str) {
        UnsafeVector<String> none;
        this->logRaw(Log::Level::Error, str, none);
    }

    void Log::fatalStr(const String& str) {
        UnsafeVector<String> none;
        String msg = this->logRaw(Log::Level::Fatal, str, none);

        this->file.flush();
        this->file.close();
        System::fail(msg);
    }

    void Log::init(void) {
        Log::initSingleton(new Log());
    }

    void Log::deinit(void) {
        Log::deinitSingleton();
    }

    template<>
    String toString<Log::Level>(Log::Level level) {
        switch(level) {
            case Log::Level::Log:
                return String("Log");

            case Log::Level::Warning:
                return String("Warining");

            case Log::Level::Error:
                return String("Error");

            case Log::Level::Fatal:
                return String("Fatal");

            default:
                return String("Unknown");
        }
    }

    template<>
    String toString<Log::Hex<uint32_t>>(Log::Hex<uint32_t> hex) {
        std::stringstream s;
        s << std::hex << hex.value;
        return s.str();
    }
}
