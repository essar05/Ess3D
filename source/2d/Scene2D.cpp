#include <Ess3D/2d/Scene2D.h>
#include <Ess3D/core/Config.h>
#include <Ess3D/2d/rendering/Renderer2D.h>

namespace Ess3D {

  Scene2D::Scene2D() {
    Config* config = Config::get();

    _camera = std::make_shared<Camera2D>();

    _camera->init((int) config->getWidth(), (int) config->getHeight(), 50.f);
    _camera->setZoom(1.0f);
    _camera->setPosition(glm::vec2(0.0f, 0.0f));
  }

  void Scene2D::render(Renderer2D *renderer) {
    renderer->render(this);
  }

  bool Scene2D::update(float deltaTime) {
    return this->onUpdate(deltaTime);
  }

  Camera2D *Scene2D::getCamera() {
    return _camera.get();
  }

  void Scene2D::setCamera(const std::shared_ptr<Camera2D>& camera) {
    _camera = camera;
  }

  void Scene2D::input(InputManager *inputManager) {
    return this->onInput(inputManager);
  }

}