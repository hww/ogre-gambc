# GambitC with ORGE Engine 

## Introduction

The Gambit Scheme system is a complete, portable, efficient and reliable implementation of the Scheme programming language. Read more here [Gambit-C Wiki](http://dynamo.iro.umontreal.ca/~gambit/wiki/index.php/Main_Page)

The OGRE (Object-Oriented Graphics Rendering Engine) is a scene-oriented, flexible 3D rendering engine [Ogre Website](http://www.ogre3d.org/)

This project is not a complette ogre to gambit-c binding. It is just an example how to complie the Ogre3D with the scheme REPL. 

What it does? It has console's overlay with REPL. Nothing else. But The rest of wrapper can be added easily because Gambit-C has a good C-interface. 

## Requirements

### Step 1

Install required files with:

```bash
   $ scripts/install-required.sh
```

### Step 2

Set the environment var OGRE_HOME to the root of this project. 

After building there will be created: bin, lib, include, share, info. Look at the example of my .bashrc file

```bash
   export OGRE_HOME=/home/valery/projects/ogre-gambc
   export PATH=:$OGRE_HOME/bin:$PATH
```
   
Or it can be more simple because next step will create symbolic link to OGRE_HOME

```bash
   export OGRE_HOME=/planet
   export PATH=:$OGRE_HOME/bin:$PATH
```

### Step 3

Make the symbolic link '/planet' to the $OGRE_HOME folder. 

```bash
   $ cd /
   $ sudo ln -s <path to project> planet
   $ sudo chown <your user name> planet
```

Note! The symbolic link required because it makes possible reffer to the project folder from places which does not support access to the environment vars.

### Step 4

Add to /etc/ld.so.conf the line /planet/lib

```bash
   $ sudo echo "/planet/lib" >> /etc/ld.so.conf
   $ sudo ldconfig
```

   Look inside scripts/install.sh to see an example.

### Step 5

Download in build the next libraries in exact same order.

   | Library | Version |
   |----------|-------|
   | OIS      |   1.3 |
   | Boost    |  1.42 |
   | Ogre     |  1.72 |
   | Gambit-C | 4.6.0 |

   The src folder has single folder for each of those libraries. Drop archives inside those folders. Each of that folders has a script build.sh wich will build and install the  library.

```bash
   $ cd src/ois
   $ ./build
```

### Step 6

Build the ogre-gambc application

```bash
   $ cd src/ogre-gambc
   $ make
   $ ./game
```

When application will run hit the key ` to see shell. Type and hit enter:

```scheme
   > (+ 1 2)
   > 3
```

![Screen Shot](/ScreenShot.png)


