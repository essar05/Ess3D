#include <Ess3D/2d/models/Entity2D.h>
#include <Ess3D/2d/utils/Utils2D.h>
#include <Ess3D/core/Config.h>

namespace Ess3D {

  Entity2D::Entity2D() = default;

  Entity2D::Entity2D(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
    Object2D(position, size, textureId, uv) {}

  void Entity2D::interpolate(float timestepAccumulatorRatio) {
    float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

    if (Config::get()->isInterpolationEnabled()) {
      this->_interpolatedPosition = timestepAccumulatorRatio * Ess3D::Utils2D::toVec2(_body->GetPosition()) +
                                    oneMinusRatio * _previousPosition;
      // TODO: have a _previousAngle.
      // TODO: ? come up with some sort of Interpolatable class to avoid having 3 separate members for one particular object property
      this->_angle = timestepAccumulatorRatio * _body->GetAngle() + oneMinusRatio * _angle;
    } else {
      this->_interpolatedPosition = Ess3D::Utils2D::toVec2(_body->GetPosition());
      // TODO: have a _previousAngle.
      // TODO: ? come up with some sort of Interpolatable class to avoid having 3 separate members for one particular object property
      this->_angle = _body->GetAngle();
    }
  }

  void Entity2D::resetInterpolation() {
    glm::vec2 position = Ess3D::Utils2D::toVec2(_body->GetPosition());
    _previousPosition = position;
  }

  void Entity2D::initializePhysicsBody(b2World *world) {
    this->initializeBody(world);
    this->initializeFixtures(world);
  }

}