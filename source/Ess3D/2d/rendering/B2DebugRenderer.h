#ifndef DAPOLIS_PONG_B2DEBUGRENDERER_H
#define DAPOLIS_PONG_B2DEBUGRENDERER_H

#include <definitions.h>
#include <Box2D/box2d.h>

namespace Ess3D {

  class API B2DebugRenderer : public b2Draw {
    public:
      void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

      void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

      void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) override;

      void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) override;

      void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

      void DrawTransform(const b2Transform &xf) override;

      void DrawPoint(const b2Vec2 &p, float size, const b2Color &color) override;

      void DrawAABB(b2AABB *aabb, const b2Color &color);
  };

  #endif

}