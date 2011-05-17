#!/bin/bash

FILE=gambc-v4_6_0-devel

if [ ! -d $FILE ]; then
mkdir $FILE 
fi

tar -xvzf $FILE.tgz -C ./

if [ -d "src" ]; then
rm src
fi

ln -s $FILE src