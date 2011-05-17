#!/bin/bash

if [ ! -d "src" ]; then
sh ./extract.sh
fi

cd src
sh ./bootstrap
./configure --prefix=$OGRE_HOME
make 
make install
cd ..