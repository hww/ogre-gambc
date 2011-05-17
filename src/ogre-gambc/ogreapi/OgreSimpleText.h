//-----------------------------------------------------------------------------
// Lonewolff
//
// Filename:    OgreText.h
// Description: Class for simple text in Ogre (Version 040507:18.30)
//-----------------------------------------------------------------------------

/**

    Usage: Using this class is as easy as doing the following;

        OgreText *textItem=new OgreText;
        textItem->setText("Hello World!");          // Text to be displayed
                                                    // Now it is possible to use the Ogre::String as parameter too
        textItem->setPos(0.1f,0.1f);                // Text position, using relative co-ordinates
        textItem->setCol(1.0f,1.0f,1.0f,0.5f);      // Text colour (Red, Green, Blue, Alpha)

    Don't forget to delete your text item after use to avoid the dreaded memory leak, like this:

        delete textItem;

    **/

#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreStringConverter.h>

using namespace Ogre;

#ifndef __OgreSimpleText_H__
#define __OgreSimpleText_H__

class OgreSimpleText
{
private:

    // Class members
    TextAreaOverlayElement *m_textArea;
    String m_elementName;

    // Static members
    static OverlayManager *m_olm;
    static OverlayContainer *m_container ;
    static Overlay *m_overlay;
    static int ms_init;
    static int ms_name;

public:
    OgreSimpleText()
    {
        if(ms_init==0)
        {
            m_olm = OverlayManager::getSingletonPtr();
            m_container = static_cast<OverlayContainer*>(m_olm->createOverlayElement("Panel","GUI"));
            m_container->setMetricsMode(Ogre::GMM_PIXELS);
            m_container->setPosition(0,0);
            m_container->setDimensions(1.0f,1.0f);
            m_overlay = m_olm->create("GUI_OVERLAY");
            m_overlay->add2D(m_container);
            m_overlay->show();
        }
        ++(this->ms_init);
        m_elementName = "element_"+StringConverter::toString(ms_name++);
        m_textArea = static_cast<TextAreaOverlayElement*>(m_olm->createOverlayElement("TextArea",m_elementName));
        m_container->addChild(m_textArea);
    }
    ~OgreSimpleText()
    {
        m_container->removeChild(m_elementName);
        m_olm->destroyOverlayElement(m_textArea);
        if(--(this->ms_init)==0)
        {
            m_overlay->remove2D(m_container);
            m_olm->destroyOverlayElement(m_container);
            m_olm->destroy(m_overlay);
        }
    }
    void setText(char *szString)
    {
        m_textArea->setCaption(szString);
        m_textArea->setDimensions(1.0f,1.0f);
        m_textArea->setMetricsMode(Ogre::GMM_RELATIVE);
        m_textArea->setFontName("Console");
        m_textArea->setCharHeight(0.03f);
    }
    void setText(String szString) // now You can use Ogre::String as text
    {
        m_textArea->setCaption(szString);
        m_textArea->setDimensions(1.0f,1.0f);
        m_textArea->setMetricsMode(Ogre::GMM_RELATIVE);
        m_textArea->setFontName("Console");
        m_textArea->setCharHeight(0.03f);
    }
    void setPosition(float x,float y)
    {
        m_textArea->setPosition(x,y);
    }
    void setColor(float R,float G,float B,float I)
    {
        m_textArea->setColour(Ogre::ColourValue(R,G,B,I));
    }
    void setColor(Ogre::ColourValue& color)
    {
        m_textArea->setColour(color);
    }
};

#endif
