#include "Scene2D.h"

#include <core/Config.h>
#include <2d/rendering/Renderer2D.h>

Ess3D::Scene2D::Scene2D() {
  Ess3D::Config* config = Ess3D::Config::get();

  _camera = std::make_shared<Ess3D::Camera2D>();

  _camera->init((int) config->getWidth(), (int) config->getHeight(), 50.f);
  _camera->setZoom(1.0f);
  _camera->setPosition(glm::vec2(0.0f, 0.0f));
}

void Ess3D::Scene2D::render(Ess3D::Renderer2D *renderer) {
  renderer->render(this);
}

bool Ess3D::Scene2D::update(float deltaTime) {
  return this->onUpdate(deltaTime);
}

Ess3D::Camera2D *Ess3D::Scene2D::getCamera() {
  return _camera.get();
}

void Ess3D::Scene2D::setCamera(const std::shared_ptr<Camera2D>& camera) {
  _camera = camera;
}

void Ess3D::Scene2D::input(Ess3D::InputManager *inputManager) {
  return this->onInput(inputManager);
}
