#pragma once

#include "definitions.h"
#include <glm/glm.hpp>

namespace Ess3D {
  struct API Vertex3D {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 uv;
  };
};