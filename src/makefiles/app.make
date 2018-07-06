FILE_NAMES_APP := app
OBJECT_FILES_APP := $(FILE_NAMES_APP:%=app/build/%.o)
CPP_FILES_APP := $(FILE_NAMES_APP:%=app/%.cpp)

CPPFLAGS_APP:= $(CPPFLAGS) -fPIC -I .
LDFLAGS_APP := $(LDFLAGS)

.PHONY: build_app

app: app/build/libapp.so

clean_app:
	-rm -r app/build/*

build_app:
	-mkdir app/build

app/build/libapp.so: Animus/build/libanimus.so build_app $(CPP_FILES_APP) $(OBJECT_FILES_APP)
	$(CPP) -shared $(LDFLAGS_APP) -o app/build/libapp.so $(OBJECT_FILES_APP)

app/build/%.o: app/%.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS_APP)
