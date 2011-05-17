#include "OgreDynamicLines.h"
#include <Ogre.h>
#include <cassert>
#include <cmath>

using namespace Ogre;

enum
{
   POSITION_BINDING
};

DynamicLines::DynamicLines(OperationType opType)
{
   initialize(opType, false);
   mDirty = true;

   iBufferSize = 2;
   prepareHardwareBuffers(iBufferSize, 0);

   //   Temp fix to remove clipping
   Vector3 vaabMin = Vector3(-1000, -1000, -1000);
   Vector3 vaabMax = Vector3(1000, 1000, 1000);
   mBox.setExtents(vaabMin, vaabMax);
}

DynamicLines::~DynamicLines()
{
}

void DynamicLines::setOperationType(OperationType opType)
{
   mRenderOp.operationType = opType;
}

RenderOperation::OperationType DynamicLines::getOperationType() const
{
   return mRenderOp.operationType;
}

void DynamicLines::drawLine(Vector3 &vectStart, Vector3 &vectEnd, ColourValue &colStart, ColourValue &colEnd)
{
   mPoints.push_back(vectStart);
   mPoints.push_back(vectEnd);
   mColors.push_back(colStart);
   mColors.push_back(colEnd);
   mDirty = true;
}

void DynamicLines::clear()
{
   mPoints.clear();
   mColors.clear();
   mDirty = true;
}

void DynamicLines::update()
{
   if(mDirty)
      fillHardwareBuffers();
}

void DynamicLines::createVertexDeclaration()
{
   VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
   decl->addElement(POSITION_BINDING, 0, VET_FLOAT3, VES_POSITION);
   decl->addElement(POSITION_BINDING, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), VET_COLOUR_ARGB, VES_DIFFUSE);
}

void DynamicLines::fillHardwareBuffers()
{
   int size = mPoints.size();

   //   Double buffer size if we have reach the maximum size
   if(iBufferSize < size)
   {
      iBufferSize = size * 2;
      prepareHardwareBuffers(iBufferSize, 0);
   }

   unsigned char *pVert;   // Will point to the start of a vertex in the HardwareVertexBuffer after it gets locked.
   float *pFloat;         // Will be used to write individual float elements of a vertex to the hardware buffer.
   Ogre::ARGB *pCol;      // Will be used to write the colour value of the vertex to the hardware buffer.

   HardwareVertexBufferSharedPtr vbuf =
      mRenderOp.vertexData->vertexBufferBinding->getBuffer(0);

   // Lock it. pVert is a pointer to the start of the hardware buffer.
   pVert = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

   // Get the element list for the buffer.
   Ogre::VertexDeclaration::VertexElementList elems = mRenderOp.vertexData->vertexDeclaration->findElementsBySource(0);

   Ogre::VertexDeclaration::VertexElementList::const_iterator elemItr, elemEnd;
   elemEnd = elems.end();

   for(int i = 0; i < iBufferSize; i++)
   {
      for (elemItr = elems.begin(); elemItr != elemEnd; ++elemItr)
      {
         // VertexElement corresponds to a part of a vertex definition eg. position, normal, colour, tex coord
         const Ogre::VertexElement& elem = *elemItr;
         switch (elem.getSemantic())
         {
            case Ogre::VES_POSITION:
               elem.baseVertexPointerToElement(pVert, &pFloat);
               if(i < size)
               {
                  *pFloat++ = mPoints[i].x;
                  *pFloat++ = mPoints[i].y;
                  *pFloat++ = mPoints[i].z;
               } else
               {
                  *pFloat++ = 0.0f;
                  *pFloat++ = 0.0f;
                  *pFloat++ = 0.0f;
               }
            break;
            case Ogre::VES_DIFFUSE:
               elem.baseVertexPointerToElement(pVert, &pCol);
               {
                  if(i < size)
                  {
                     *pCol++ = Ogre::VertexElement::convertColourValue(Ogre::ColourValue(mColors[i].r, mColors[i].g, mColors[i].b, mColors[i].a), Ogre::VET_COLOUR_ARGB);
                  } else
                  {
                     *pCol++ = Ogre::VertexElement::convertColourValue(Ogre::ColourValue(0.0, 0.0, 0.0, 0.0), Ogre::VET_COLOUR_ARGB);
                  }
               }
            break;
         } // Deal with an individual vertex element.
      } // Loop vertex elements.
      pVert += vbuf->getVertexSize();
   }
   vbuf->unlock();
   mDirty = false;
   clear();
}
