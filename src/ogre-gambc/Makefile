## Compiler and linker settings
PROJECT_HOME = $(OGRE_HOME)/src/ogre-gambc
PROJECT_DIST = $(OGRE_HOME)
PKG_CONFIG_PATH = $(OGRE_HOME)/lib/pkgconfig
GAMBC_HOME = $(OGRE_HOME)

DEBUG = 1
ifdef DEBUG
	DEFINES = -g3 -pipe
	GSC = gsc -debug -cc-options "-g3"
else
	DEFINES = -march=native -O2 -fomit-frame-pointer -pipe
	GSC = gsc -cc-options "-D___SINGLE_HOST" 
endif


LIBS = OIS
CXX = g++
CFLAGS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(LIBS))	\
	$(DEFINES)	\
	-I$(OGRE_HOME)/include \
	-I$(OGRE_HOME)/include/OGRE \
	-I$(OGRE_HOME)/include 
CXXFLAGS = $(CFLAGS)

LD = g++
LDFLAGS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(LIBS))	\
	-L$(OGRE_HOME)/lib -lOgreMain -lpthread	\
	-L$(GAMBC_HOME)/lib \
	-lutil -lgambc

LINK = ar

export CXX CFLAGS CXXFLAGS LD LINK GSC

## Compilation and linking occurs here
all: game

scmapi/ScmAPI.a:
	$(MAKE) -C scmapi

## Files to include in yourApp project
SAMPLEAPP_CPP = app/BaseApplication.cpp \
			app/Game.cpp \
			ogreapi/OgreScreenCoords.cpp \
			ogreapi/OgreConsole.cpp \
			ogreapi/OgreEditString.cpp \
			ogreapi/OgreDynamicLines.cpp \
			ogreapi/OgreDynamicRenderable.cpp \
			ogreapi/OgreSimpleText.cpp 

#			core/CoreTypes.cpp \
#			core/CoreCRC32.cpp \
#			core/CoreHash.cpp \
#			core/CoreDoubleList.cpp \
#			dbg/DebugDrawManager.cpp \
#			dbg/DebugDrawElement.cpp \
#			ogreapi/OgreScreenCoords.cpp \
#			ogreapi/OgreConsole.cpp \
#			ogreapi/OgreEditString.cpp \
#			ogreapi/OgreDynamicLines.cpp \
#			ogreapi/OgreDynamicRenderable.cpp \
#			ogreapi/OgreSimpleText.cpp 

%.o : %.cpp
		$(COMPILE.cpp) -MD -o $@ $<
		@cp $*.d $*.P; \
			sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
				-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include $(SAMPLEAPP_CPP:.cpp=.P)

SAMPLEAPP = $(SAMPLEAPP_CPP:.cpp=.o)

game: $(SAMPLEAPP) scmapi/ScmAPI.a
	$(LD) $(SAMPLEAPP) scmapi/ScmAPI.a -o game $(LDFLAGS)

## Clean up
clean:
	rm -f $(SAMPLEAPP) game $(SAMPLEAPP_CPP:.cpp=.d) $(SAMPLEAPP_CPP:.cpp=.P)
	$(MAKE) -C scmapi clean
