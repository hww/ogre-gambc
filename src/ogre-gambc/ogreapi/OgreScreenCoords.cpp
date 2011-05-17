#include "OgreScreenCoords.h"
#include <OgrePlane.h>

using namespace Ogre;

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
bool getScreenspaceCoords(Ogre::MovableObject* object, Ogre::Camera* camera, Ogre::Vector2& result)
{
   if(!object->isInScene())
      return false;

   const AxisAlignedBox &AABB = object->getWorldBoundingBox(true);

   /**
   * If you need the point above the object instead of the center point:
   * This snippet derives the average point between the top-most corners of the bounding box
   * Ogre::Vector3 point = (AABB.getCorner(AxisAlignedBox::FAR_LEFT_TOP)
   *    + AABB.getCorner(AxisAlignedBox::FAR_RIGHT_TOP)
   *    + AABB.getCorner(AxisAlignedBox::NEAR_LEFT_TOP)
   *    + AABB.getCorner(AxisAlignedBox::NEAR_RIGHT_TOP)) / 4;
   */

   // Get the center point of the object's bounding box
   Vector3 point = AABB.getCenter();

   // Is the camera facing that point? If not, return false
   Plane cameraPlane = Plane(Ogre::Vector3(camera->getDerivedOrientation().zAxis()), camera->getDerivedPosition());
   if(cameraPlane.getSide(point) != Plane::NEGATIVE_SIDE)
      return false;

   // Transform the 3D point into screen space
   point = camera->getProjectionMatrix() * (camera->getViewMatrix() * point);

   // Transform from coordinate space [-1, 1] to [0, 1] and update in-value
   result.x = (point.x / 2) + 0.5f;
   result.y = 1 - ((point.y / 2) + 0.5f);

   return true;
}

bool getScreenspaceCoords(Ogre::Vector3& point, Ogre::Camera* camera, Ogre::Vector2& result)
{
   // Is the camera facing that point? If not, return false
   Plane cameraPlane = Plane(Ogre::Vector3(camera->getDerivedOrientation().zAxis()), camera->getDerivedPosition());
   if(cameraPlane.getSide(point) != Plane::NEGATIVE_SIDE)
      return false;

   // Transform the 3D point into screen space
   point = camera->getProjectionMatrix() * (camera->getViewMatrix() * point);

   // Transform from coordinate space [-1, 1] to [0, 1] and update in-value
   result.x = (point.x / 2) + 0.5f;
   result.y = 1 - ((point.y / 2) + 0.5f);

   return true;
}
