/*=====================================================<
** -- OgreB2DebugDraw.cpp v1.0
*> Box2D debug drawing implementation using Ogre graphics.
*> Copyright (c) 2009, Stephan Aelmore
**
*> This code is provided 'as-is', without any express or implied warranty.
*> In no event will the author be held liable for any damages arising from the
*> use of this code.
**
*> Permission is granted to anyone to use this code for any purpose,
*> including commercial applications, and to alter it and redistribute it
*> freely, subject to the following restrictions:
**
*> 1. If you use this code or a derivation thereof, you must cite the origin
*> of the code, giving credit to the author for the original work.
**
*> 2. If you alter the source in any way (the most likely circumstance, given
*> the nature of the code), then you must mark it as such, and not misrepresent
*> the altered work as the original code.
**
>=====================================================*/

#include "OgreB2DebugDraw.h"

OgreB2DebugDraw::OgreB2DebugDraw(Ogre::SceneManager* scene, const char* material, float fillAlpha, Ogre::uint8 renderQueueGroup) :
    b2DebugDraw(),
    m_scene(scene),
    m_material(material),
    m_fillAlpha(fillAlpha),
    m_shapes()
{
    // Create the manual object.
    m_shapes = m_scene->createManualObject("OgreB2DebugDrawShapes");
    m_scene->getRootSceneNode()->createChildSceneNode("OgreB2DebugDrawNode")->attachObject(m_shapes);

    // Make it dynamic since we will be rewriting the data many times each frame.
    m_shapes->setDynamic(true);

    // Add it to the given render queue group to control render order.
    m_shapes->setRenderQueueGroup(renderQueueGroup);
}
OgreB2DebugDraw::~OgreB2DebugDraw()
{
    m_scene->destroyManualObject("OgreB2DebugDrawShapes");
    m_scene->destroySceneNode("OgreB2DebugDrawNode");
}

void OgreB2DebugDraw::clear()
{
    m_shapes->clear();
}

Ogre::ManualObject* OgreB2DebugDraw::BuildPolygon(Ogre::ManualObject* man, const b2Vec2* vertices,
                                             int32 vertexCount, const b2Color& color, float alpha)
{
    // We estimate the vertex count beforehand to optimize allocation.
    // Note that we add one since Box2D does not count overlap vertex.
    man->estimateVertexCount(vertexCount+1);

    // Place the vertices.
    for (int32 i = 0; i < vertexCount; ++i)
   {
      man->position(vertices[i].x, vertices[i].y, 0);
      man->colour(color.r, color.g, color.b, alpha);
   }
   // Place the overlap vertex at position 0.
   man->position(vertices[0].x, vertices[0].y, 0);
   man->colour(color.r, color.g, color.b, alpha);
}

Ogre::ManualObject* OgreB2DebugDraw::BuildCircle(Ogre::ManualObject* man, const b2Vec2& center,
                                            float32 radius, const b2Color& color, float alpha)
{
    // circle variables
   const float k_segments = 32.0f;
   const float k_increment = 2.0f * b2_pi / k_segments;
   float theta = 0.0f;

   // We estimate the vertex count beforehand to optimize allocation.
    // Note that we add one since Box2D does not count overlap vertex.
    man->estimateVertexCount(k_segments+1);

    // Update object data.
    b2Vec2 v;
    for (int32 i = 0; i < k_segments; ++i)
   {
      v = center + radius * b2Vec2(cosf(theta), sinf(theta));
      man->position(v.x, v.y, 0);
      man->colour(color.r, color.g, color.b, alpha);
      theta += k_increment;
   }
   // Place the overlap vertex at the start position.
   v = center + b2Vec2(radius, 0.0f);
   man->position(v.x, v.y, 0);
    man->colour(color.r, color.g, color.b, alpha);
}

Ogre::ManualObject* OgreB2DebugDraw::BuildSegment(Ogre::ManualObject* man, const b2Vec2& p1,
                                             const b2Vec2& p2, const b2Color& color, float alpha)
{
    // We estimate the vertex count beforehand to optimize allocation.
    man->estimateVertexCount(2);

    // Place the first vertex.
    man->position(p1.x, p1.y, 0);
    man->colour(color.r, color.g, color.b, alpha);

    // Place the second vertex.
   man->position(p2.x, p2.y, 0);
   man->colour(color.r, color.g, color.b, alpha);
}

void OgreB2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    // Begin new edge section.
    m_shapes->begin(m_material, Ogre::RenderOperation::OT_LINE_STRIP);

    // Call helper method to generate vertex data.
    BuildPolygon(m_shapes, vertices, vertexCount, color);

    // Finalize the section.
    m_shapes->end();
}

void OgreB2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
   // Begin new edge section.
    m_shapes->begin(m_material, Ogre::RenderOperation::OT_LINE_STRIP);

    // Call helper method to generate vertex data.
    BuildPolygon(m_shapes, vertices, vertexCount, color);

    // Finalize the section.
    m_shapes->end();

    // Only fill if it will be visible.
    if (m_fillAlpha > 0.01f)
    {
        // Begin new fill section.
        m_shapes->begin(m_material, Ogre::RenderOperation::OT_TRIANGLE_FAN);

        // Call helper method to generate vertex data.
        BuildPolygon(m_shapes, vertices, vertexCount, color, m_fillAlpha);

        // Finalize the section.
        m_shapes->end();
    }
}

void OgreB2DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    // Begin new edge section.
    m_shapes->begin(m_material, Ogre::RenderOperation::OT_LINE_STRIP);

    // Call helper method to generate vertex data.
    BuildCircle(m_shapes, center, radius, color);

    // Finalize the section.
    m_shapes->end();
}

void OgreB2DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    // Begin new edge section.
    m_shapes->begin(m_material, Ogre::RenderOperation::OT_LINE_STRIP);

    // Call helper method to generate vertex data.
    BuildCircle(m_shapes, center, radius, color);

    // Finalize the section.
    m_shapes->end();

    // Only fill if it will be visible.
    if (m_fillAlpha > 0.01f)
    {
        // Begin new fill section.
        m_shapes->begin(m_material, Ogre::RenderOperation::OT_TRIANGLE_FAN);

        // Call helper method to generate vertex data.
        BuildCircle(m_shapes, center, radius, color, m_fillAlpha);

        // Finalize the section.
        m_shapes->end();
    }
}

void OgreB2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    // Begin new edge section.
    m_shapes->begin(m_material, Ogre::RenderOperation::OT_LINE_LIST);

    // Call helper method to generate vertex data.
    BuildSegment(m_shapes, p1, p2, color);

    // Finalize the section.
    m_shapes->end();
}

void OgreB2DebugDraw::DrawXForm(const b2XForm& xf)
{
   // XForm data
   b2Vec2 p1 = xf.position, p2;
   const float32 k_axisScale = 1.0f;

   // Begin new edge section.
    m_shapes->begin(m_material, Ogre::RenderOperation::OT_LINE_LIST);

    // Add a red segment.
    p2 = p1 + k_axisScale * xf.R.col1;
    BuildSegment(m_shapes, p1, p2, b2Color(1,0,0));

    // Add a green segment.
   p2 = p1 + k_axisScale * xf.R.col2;
    BuildSegment(m_shapes, p1, p2, b2Color(0,1,0));

    // Finalize the section.
    m_shapes->end();
}
