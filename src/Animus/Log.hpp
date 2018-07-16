#ifndef ANIMUS_LOG
#define ANIMUS_LOG

#include "Singleton.hpp"
#include "File.hpp"
#include "Object.hpp"
#include "types/types.hpp"
#include "System.hpp"
#include "types/Vector.hpp"

namespace Animus {
    class Log : public Singleton<Log>, public Object {
        File file;

        Log(void);

        template<typename T>
        static void argsToVector(UnsafeVector<String>& strings, T value) {
            strings.push_back(toString<T>(value));
        }

        template<typename T, typename... ARGS>
        static void argsToVector(UnsafeVector<String>& strings, T value, ARGS... args) {
            strings.push_back(toString<T>(value));
            Log::argsToVector(strings, args...);
        }
    public:
        enum class Level {
            Log,
            Warning,
            Error,
            Fatal
        };

        //wrapper to print numbers as hex
        template<typename I>
        struct Hex {
            I value;

            Hex(I value) {
                this->value = value;
            }
            ~Hex(void) = default;
        };

        ~Log(void);

        void logStr(const String& str);
        void warnStr(const String& str);
        void errorStr(const String& str);
        void fatalStr(const String& str);

        template<typename... ARGS>
        void log(const String& message, ARGS... args) {
            UnsafeVector<String> strings;
            Log::argsToVector(strings, args...);
            this->logRaw(Log::Level::Log, message, strings);
        }

        template<typename... ARGS>
        void warn(const String& message, ARGS... args) {
            UnsafeVector<String> strings;
            Log::argsToVector(strings, args...);
            this->logRaw(Log::Level::Warning, message, strings);
        }


        template<typename... ARGS>
        void error(const String& message, ARGS... args) {
            UnsafeVector<String> strings;
            Log::argsToVector(strings, args...);
            this->logRaw(Log::Level::Error, message, strings);
        }

        template<typename... ARGS>
        [[noreturn]] void fatal(const String& message, ARGS... args) {
            UnsafeVector<String> strings;
            Log::argsToVector(strings, args...);
            String msg = this->logRaw(Log::Level::Fatal, message, strings);

            this->file.flush();
            this->file.close();
            System::fail(msg);
        }

        static void init(void);
        static void deinit(void);

    private:
        ANIMUS_REQUIRES_STD
        String logRaw(Log::Level level, const String& fmt, const UnsafeVector<String>& args);
    };

    template<>
    String toString<Log::Level>(Log::Level level);

    ANIMUS_REQUIRES_STD
    template<>
    String toString<Log::Hex<uint32_t>>(Log::Hex<uint32_t>);
}
#endif
