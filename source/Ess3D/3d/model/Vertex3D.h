#pragma once

#include <glm/glm.hpp>

namespace Ess3D {
  struct Vertex3D {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 uv;
  };
};