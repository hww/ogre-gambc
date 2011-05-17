#!/bin/bash

if [ ! -d "src" ]; then
sh ./extract.sh
fi

cd src
./configure --enable-cplusplus --enable-single-host --prefix=$OGRE_HOME
make bootstrap
make
make install
cd ..