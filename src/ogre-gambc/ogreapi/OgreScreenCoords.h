#ifndef _OGRE_SCREEN_COORDS_H_
#define _OGRE_SCREEN_COORDS_H_

#include <OgreMovableObject.h>
#include <OgreCamera.h>
#include <Ogre.h>

/**
* This little snippet gets the screenspace coordinates for a MovableObject
*
* @param   object   The object to retrieve the coordidnates of.
* @param   camera   The active camera
* @param   result   The Vector2 to store the result in
*
* @return   Returns true if the object is visible and the coordinates were
*         retrieved, false otherwise.
*/
bool getScreenspaceCoords(Ogre::MovableObject* object, Ogre::Camera* camera, Ogre::Vector2& result);

/**
* This little snippet gets the screenspace coordinates for a MovableObject
*
* @param   point    The world position.
* @param   camera   The active camera
* @param   result   The Vector2 to store the result in
*
* @return   Returns true if the object is visible and the coordinates were
*         retrieved, false otherwise.
*/
bool getScreenspaceCoords(Ogre::Vector3& point, Ogre::Camera* camera, Ogre::Vector2& result);

#endif
