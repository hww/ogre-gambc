#!/bin/bash
FILE=boost_1_42_0
if [ ! -d $FILE ]; then
tar -xvjf $FILE.tar.bz2 -C ./
fi

if [ -d src ]; then
rm src
fi

ln -s $FILE src




