#!/bin/sh

cd build
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./animus-loader
