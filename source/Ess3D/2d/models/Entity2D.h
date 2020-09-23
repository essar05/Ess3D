#pragma once

#include <2d/models/Object2D.h>
#include <Box2D/box2d.h>
#include <memory>
#include <definitions.h>

namespace Ess3D {

  class API Entity2D : public Object2D {
    public:
      Entity2D();

      Entity2D(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv);

      void interpolate(float timestepAccumulatorRatio) override;

      void resetInterpolation() override;

      virtual void initializePhysicsBody(b2World *world);

    protected:
      b2Body *_body;

      virtual void initializeBody(b2World *world) = 0;

      virtual void initializeFixtures(b2World *world) = 0;
  };

}