#!/bin/bash

rm -rf buildIOTA /
mkdir buildIOTA && cd buildIOTA
cmake -DCMAKE_TOOLCHAIN_FILE=../cross-esp32.cmake ../../../
make
cd ..

make
