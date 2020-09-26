#pragma once

#include <memory>
#include <Ess3D/2d/traits/IRenderable2D.h>
#include <Ess3D/core/traits/IHandlesInput.h>
#include <Ess3D/core/traits/IUpdatable.h>
#include <Ess3D/2d/camera/Camera2D.h>

namespace Ess3D {

  class API Scene2D : public IUpdatable, public IRenderable2D, public IHandlesInput {
    friend class Renderer2D;

    public:
      Scene2D();

      bool update(float deltaTime) final;
      void input(InputManager* inputManager) final;
      void render(Renderer2D *renderer) final;

      virtual Camera2D* getCamera();
      virtual void setCamera(const std::shared_ptr<Camera2D> &camera);

    protected:
      std::shared_ptr<Camera2D> _camera;

  };

}