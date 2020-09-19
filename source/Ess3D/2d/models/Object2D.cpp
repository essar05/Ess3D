#pragma once

#include "Object2D.h"
#include <core/State.h>
#include <2d/rendering/Renderer2D.h>

namespace Ess3D {

  Object2D::Object2D() = default;

  Object2D::Object2D(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
    Object2D(position, size, textureId, uv, Ess3D::ColorRGBA8(225, 255, 255, 255)) {}

  Object2D::Object2D(
    const glm::vec2 &position, const glm::vec2 &size, GLuint textureId,
    const glm::vec4 &uv, Ess3D::ColorRGBA8 color
 ) {
    setPosition(position);
    setSize(size);
    setTextureId(textureId);
    setUV(uv);
    setColor(color);
  }

  bool Object2D::update(float deltaTime) {
    // remembers previous state, before update overrides it with the new state
    this->resetInterpolation();

    // executes custom update code
    return this->onUpdate(deltaTime);
  }

  void Object2D::input(InputManager *inputManager) {
    this->onInput(inputManager);
  }

  void Object2D::render(Renderer2D *renderer) {
    // interpolate values based on the timestep accumulator (% of time to take another full, fixed delta time, physics update step)
    this->interpolate(State::get()->getTimestepAccumulator()->getAccumulatorRatio());

    // executes custom render code
    this->onRender(renderer);
  }

  bool Object2D::onUpdate(float deltaTime) {
    return IUpdatable::onUpdate(deltaTime);
  }

  void Object2D::onRender(Renderer2D *renderer) {
    Sprite sprite;
    sprite.position = _interpolatedPosition;
    sprite.size = _size;
    sprite.uv = _uv;
    sprite.textureId = _textureId;
    sprite.color = _color;
    sprite.zDepth = 9000.0f;
    sprite.angle = glm::radians(0.0f);

    renderer->addToRenderQueue(sprite);
  }

  void Object2D::interpolate(float timestepAccumulatorRatio) {
    float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

    this->_interpolatedPosition = timestepAccumulatorRatio * _position +
                                  oneMinusRatio * _previousPosition;
  }

  void Object2D::resetInterpolation() {
    _previousPosition = _position;
  }

  GLuint Object2D::getTextureId() const {
    return this->_textureId;
  }

  void Object2D::setTextureId(GLuint textureId) {
    this->_textureId = textureId;
  }

  glm::vec4 Object2D::getUV() {
    return this->_uv;
  }

  void Object2D::setUV(const glm::vec4& uv) {
    this->_uv = uv;
  }

  Ess3D::ColorRGBA8 Object2D::getColor() {
    return this->_color;
  }

  void Object2D::setColor(Ess3D::ColorRGBA8 color) {
    this->_color = color;
  }

  glm::vec2 Object2D::getSize() {
    return this->_size;
  }

  void Object2D::setSize(const glm::vec2& size) {
    this->_size = size;
  }

  glm::vec2 Object2D::getPreviousPosition() {
    return this->_previousPosition;
  }

  void Object2D::setPreviousPosition(const glm::vec2& previousPosition) {
    this->_previousPosition = previousPosition;
  }

  glm::vec2 Object2D::getPosition() {
    return this->_position;
  }

  void Object2D::setPosition(const glm::vec2& position) {
    this->_position = position;
  }

  glm::vec2 Object2D::getInterpolatedPosition() {
    return this->_interpolatedPosition;
  }

  void Object2D::setInterpolatedPosition(const glm::vec2& interpolatedPosition) {
    this->_interpolatedPosition = interpolatedPosition;
  }

}
