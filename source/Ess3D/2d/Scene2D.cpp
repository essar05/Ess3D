#include "Scene2D.h"

#include <utility>
#include <core/Config.h>
#include <2d/camera/Camera2D.h>

Ess3D::Scene2D::Scene2D() {
  Ess3D::Config* config = Ess3D::Config::get();

  _camera = std::make_shared<Ess3D::Camera2D>();

  _camera->init((int) config->getWidth(), (int) config->getHeight(), 50.f);
  _camera->setZoom(1.0f);
  _camera->setPosition(glm::vec2(0.0f, 0.0f));
}

Ess3D::Camera2D *Ess3D::Scene2D::getCamera() {
  return _camera.get();
}

void Ess3D::Scene2D::setCamera(const std::shared_ptr<Camera2D>& camera) {
  _camera = camera;
}
