#pragma once

#include "definitions.h"
#include <glm/glm.hpp>
#include <box2d/box2d.h>

namespace Ess3D {
  class API Utils {
    public:
      static glm::vec2 rotatePoint(const glm::vec2& point, const glm::vec2& pivot, float angle);

    private:
      Utils();
  };
}

