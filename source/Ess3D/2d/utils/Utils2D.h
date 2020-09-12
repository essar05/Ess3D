#pragma once

#include "definitions.h"
#include <glm/glm.hpp>
#include <box2d/box2d.h>

namespace Ess3D {
  class API Utils2D {
    public:
      static glm::vec2 toVec2(const b2Vec2& vector);
      static b2Vec2 toB2Vec2(const glm::vec2& vector);

    private:
      Utils2D();
  };
}

