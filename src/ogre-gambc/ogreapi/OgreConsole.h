#ifndef _OGRE_CONSOLE_H
#define _OGRE_CONSOLE_H

//#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreFrameListener.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OIS.h>
#include <list>
#include <string>
#include "OgreEditString.h"

#include "../scmapi/ScmRepl.h"
 
class OgreConsole: public Ogre::Singleton<OgreConsole>, Ogre::FrameListener, Ogre::LogListener
{
public:
    OgreConsole();
    virtual ~OgreConsole();

    void    init(Ogre::Root *root);
    void    shutdown();
    void    setVisible(bool fVisible);
    bool    isVisible(){ return visible; }
    void    print( std::string text );
    bool    injectKeyPress( const OIS::KeyEvent &evt );

    // Frame listener
    bool    frameStarted(const Ogre::FrameEvent &evt);
    bool    frameEnded(const Ogre::FrameEvent &evt);

    // Log Listener
    void    messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName );

protected:
    static const float CURSOR_BLINKING_SPEED = 0.25f;
    
    bool                    visible;
    bool                    textChanged;
    float                   height;
    int                     start_line;
    bool                    cursor_blink;
    float                   cursor_blinkTime;

    Ogre::Overlay           *overlay;
    Ogre::OverlayContainer  *panel;
    Ogre::OverlayElement    *textbox;
    Ogre::Root              *root;

    EditString              editline;
    ScmRepl			        *interpreter;

    std::list<std::string>  lines;
    std::list<std::string>  history;
 
    std::list<std::string>::iterator    history_line;
 
    void    addToHistory( const std::string& cmd );
};
 
#endif // _OGRE_CONSOLE_H
