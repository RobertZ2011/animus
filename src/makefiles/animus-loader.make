FILE_NAMES_ANIMUS_LOADER := main
OBJECT_FILES_ANIMUS_LOADER := $(FILE_NAMES_ANIMUS_LOADER:%=animus-loader/build/%.o)
CPP_FILES_ANIMUS_LOADER := $(FILE_NAMES_ANIMUS_LOADER:%=animus-loader/%.cpp)

CPPFLAGS_ANIMUS_LOADER := $(CPPFLAGS) -I .
LDFLAGS_ANIMUS_LOADER := $(LDFLAGS) -lanimus -L Animus/build

.PHONY: build_animus_loader

animus_loader: animus-loader/build/animus-loader

clean_animus_loader:
	-rm -r animus-loader/build/*

build_animus_loader:
	-mkdir animus-loader/build

animus-loader/build/animus-loader: animus build_animus_loader $(CPP_FILES_ANIMUS_LOADER) $(OBJECT_FILES_ANIMUS_LOADER)
	$(CPP) $(LDFLAGS_ANIMUS_LOADER) -o animus-loader/build/animus-loader $(OBJECT_FILES_ANIMUS_LOADER)

animus-loader/build/%.o: animus-loader/%.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS_ANIMUS_LOADER)
