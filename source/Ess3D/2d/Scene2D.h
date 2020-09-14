#pragma once

#include <2d/camera/Camera2D.h>
#include "rendering/Renderer2D.h"

namespace Ess3D {

  class Renderer2D;

  class API Scene2D {
    public:
      Scene2D();

      virtual void render(Renderer2D *renderer) = 0;
      virtual void update(float deltaTime) = 0;

      virtual void interpolate(float timestepAccumulatorRatio) = 0;
      virtual void resetInterpolation() = 0;

      virtual Camera2D* getCamera();
      virtual void setCamera(const std::shared_ptr<Camera2D> &camera);

    protected:
      std::shared_ptr<Camera2D> _camera;

  };

}