CPP := clang++
CPPFLAGS := --std=c++11 -g -Wall
LDFLAGS := -g

include makefiles/Animus.make
include makefiles/animus-loader.make
include makefiles/app.make

.PHONY: build

build:
	-mkdir build

all: animus animus_loader app build
	cp Animus/build/libanimus.so build/
	cp animus-loader/build/animus-loader build/
	cp app/build/libapp.so build/

clean: clean_animus clean_animus_loader clean_app
	-rm -r build
