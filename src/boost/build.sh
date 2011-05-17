#!/bin/bash
if [ ! -d "src" ]; then
sh ./extract.sh
fi

cd src
./bootstrap.sh
./bjam install --prefix=$OGRE_HOME
cd ..

