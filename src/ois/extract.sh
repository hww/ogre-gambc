#!/bin/bash

FILE=ois-v1-3

if [ ! -d $FILE ]; then
mkdir $FILE 
fi

tar -xvzf $FILE.tar.gz 

if [ -d "src" ]; then
rm src
fi

ln -s $FILE src