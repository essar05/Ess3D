#include "Utils2D.h"

glm::vec2 Ess3D::Utils2D::toVec2(const b2Vec2& vector) {
  return glm::vec2(vector.x, vector.y);
}

b2Vec2 Ess3D::Utils2D::toB2Vec2(const glm::vec2& vector) {
  return b2Vec2(vector.x, vector.y);
}