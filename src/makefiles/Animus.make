FILE_NAMES_ANIMUS := AtomicObject FilePath SharedObject ThreadPool Animus
OBJECT_FILES_ANIMUS := $(FILE_NAMES_ANIMUS:%=Animus/build/%.o)
CPP_FILES_ANIMUS := $(FILE_NAMES_ANIMUS:%=Animus/%.cpp)

CPPFLAGS_ANIMUS := $(CPPFLAGS) -fPIC
LDFLAGS_ANIMUS := $(LDFLAGS) -lSDL2

.PHONY: build_animus

animus: Animus/build/libanimus.so

clean_animus:
	-rm -r Animus/build/*

build_animus:
	-mkdir Animus/build

Animus/build/libanimus.so: build_animus $(CPP_FILES_ANIMUS) $(OBJECT_FILES_ANIMUS)
	$(CPP) -shared $(LDFLAGS_ANIMUS) -o Animus/build/libanimus.so $(OBJECT_FILES_ANIMUS)

Animus/build/%.o: Animus/%.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS_ANIMUS)
