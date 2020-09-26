#include <Ess3D/utils/Utils.h>

namespace Ess3D {

  Utils::Utils() = default;

  glm::vec2 Utils::rotatePoint(const glm::vec2 &point, const glm::vec2 &pivot, float angle) {
    glm::vec2 newPoint;

    newPoint.x = (point.x - pivot.x) * cos(angle) - (point.y - pivot.y) * sin(angle) + pivot.x;
    newPoint.y = (point.x - pivot.x) * sin(angle) + (point.y - pivot.y) * cos(angle) + pivot.y;

    return newPoint;
  }

}