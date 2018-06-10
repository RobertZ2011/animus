CPP := clang++
CPPFLAGS := --std=c++17 -g -Wall -Werror -DANIMUS_USE_STD -DANIMUS_ALLOW_TODO -DANIMUS_USE_SDL -DDEBUG
AR := ar
LDFLAGS := -g

include makefiles/Animus.make
include makefiles/animus-loader.make
include makefiles/app.make
include makefiles/vulkan.make

.PHONY: build

build:
	-mkdir -p build/backends

all: animus backends animus_loader app build
	cp Animus/build/libanimus.so build/
	cp animus-loader/build/animus-loader build/
	cp app/build/libapp.so build/
	cp Animus/build/backends/* build/backends

backends: vulkan

clean: clean_animus clean_animus_loader clean_app
	-rm -r build
