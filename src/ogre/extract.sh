#!/bin/bash

FILE=ogre_src_v1-7-2

if [ ! -d $FILE ]; then
mkdir $FILE 
fi

tar -xvjf $FILE.tar.bz2

if [ -d "src" ]; then
rm src
fi

ln -s $FILE src
