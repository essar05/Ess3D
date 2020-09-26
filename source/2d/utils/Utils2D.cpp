#include <Ess3D/2d/utils/Utils2D.h>

namespace Ess3D {

  glm::vec2 Utils2D::toVec2(const b2Vec2 &vector) {
    return glm::vec2(vector.x, vector.y);
  }

  b2Vec2 Utils2D::toB2Vec2(const glm::vec2 &vector) {
    return b2Vec2(vector.x, vector.y);
  }

}