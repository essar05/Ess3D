#pragma once

#include <glm/glm.hpp>

namespace Ess3D {
  struct Vertex3D {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
  };
};