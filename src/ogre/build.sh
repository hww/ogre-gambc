#!/bin/bash

if [ ! -d "src" ]; then
sh ./extract.sh
fi

if [ ! -d "build" ]; then
mkdir build
fi

cd build
cmake -DCMAKE_INSTALL_PREFIX=$OGRE_HOME -DOGRE_INSTALL_SAMPLES=ON  -DCMAKE_BUILD_TYPE=RelWithDebInfo ../src 
make
make install
cd ..
