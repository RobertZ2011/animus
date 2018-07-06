#ifndef ANIMUS_ARGUMENTS
#define ANIMUS_ARGUMENTS

namespace Animus {
    class Arguments {
        Vector<String> flags;
        Map<String, String> values;

    public:
        Arguments(int argc, const char **argv);
        ~Arguments(void) = default;

        bool hasFlag(const String& shortName, const Optional<String>& longName = Optional<String>());
        String getString(const String& shortName, const Optional<String>& longName = Optional<String>());

        template<typename T>
        T getValue(const String& shortName, const Optional<String>& longName = Optional<String>());
    }

    template<typename T>
    T Arguments::getValue(const String& shortName, Optional<String> longName = Optional<String>()) {
        String str = this->getString(shortName, longName);
        return fromString<T>(str);
    }
}
#endif