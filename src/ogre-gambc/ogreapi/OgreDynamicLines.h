#ifndef _DYNAMIC_LINES_H_
#define _DYNAMIC_LINES_H_

#include "OgreDynamicRenderable.h"
#include <vector>

using namespace Ogre;

/* Render lines with different colors
	@remarks
		To Init :
			pLines = new DynamicLines(RenderOperation::OT_LINE_LIST);
			SceneNode *pLinesNode = pSceneMgr->getRootSceneNode()->createChildSceneNode("DynamicLines");
			pLinesNode->attachObject(pLines);
			pLines->setMaterial("Lines/VertexColor");

		Every frame, call this :
			for(int i = 0; i < 10; ++i)
				pLines->drawLine(Vector3(-1, i, 0), Vector3(1, i, 0), ColourValue(0.5, 0.5, 0.5, 1.0), ColourValue(0.5, 0.5, 0.5, 1.0));

		Call update once per frame in a frameStarted function :
			pLines->update(); */

class DynamicLines : public DynamicRenderable
{
   int iBufferSize;
   typedef Ogre::Vector3 Vector3;
   typedef Ogre::Quaternion Quaternion;
   typedef Ogre::Camera Camera;
   typedef Ogre::Real Real;
   typedef Ogre::RenderOperation::OperationType OperationType;

private:
   std::vector<Vector3> mPoints;
   std::vector<ColourValue> mColors;
   bool mDirty;

public:
   /// Constructor - see setOperationType() for description of argument.
   DynamicLines(OperationType opType=Ogre::RenderOperation::OT_LINE_STRIP);
   virtual ~DynamicLines();

   void drawLine(Vector3 &vectStart, Vector3 &vectEnd, ColourValue &colStart, ColourValue &colEnd);
   void clear();      /// Remove all points from the point list
   void update();     /// Call this to update the hardware buffer after making changes.

   /** Set the type of operation to draw with.
   * @param opType Can be one of
   *    - RenderOperation::OT_LINE_STRIP
   *    - RenderOperation::OT_LINE_LIST
   *    - RenderOperation::OT_POINT_LIST
   *    - RenderOperation::OT_TRIANGLE_LIST
   *    - RenderOperation::OT_TRIANGLE_STRIP
   *    - RenderOperation::OT_TRIANGLE_FAN
   *    The default is OT_LINE_STRIP.
   */
   void setOperationType(OperationType opType);
   OperationType getOperationType() const;

protected:
   /// Implementation DynamicRenderable, creates a simple vertex-only decl
   virtual void createVertexDeclaration();
   /// Implementation DynamicRenderable, pushes point list out to hardware memory
   virtual void fillHardwareBuffers();
};

#endif
