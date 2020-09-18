#include "Camera2D.h"

namespace Ess3D {
  Camera2D::Camera2D(): 
    _position(0.0f, 0.0f), 
    _cameraMatrix(1.0f), 
    _scale(1.0f), 
    _doUpdate(true),
    _screenWidth(640), 
    _screenHeight(480),
    _orthoMatrix(1) {}

  Camera2D::~Camera2D() = default;

  void Camera2D::setInterpolatedPosition(const glm::vec2& interpolatedPosition) {
    _interpolatedPosition = interpolatedPosition;
  }

  void Camera2D::init(int screenWidth, int screenHeight, float cameraWidth) {
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    float screenAspectRatio = (float) _screenWidth / (float) _screenHeight;

    _width = cameraWidth;
    // scaling the height of the camera to match the entirety of the screen
    _height = cameraWidth / screenAspectRatio;

    // calculate the world to screen scaling factor (how many pixels there are in a world unit)
    _scale = (float) _screenWidth / _width;

    // orthographic projection matrix so that we will see _width * _height world units on the screen, with the center in point 0, 0
    _orthoMatrix = glm::ortho(- _width / 2, _width / 2, - _height / 2, _height / 2);

    this->update();
  }

  void Camera2D::update() {
    if (_doUpdate) {
      _cameraMatrix = _orthoMatrix;

      // move the camera to the desired position
      glm::vec3 translation(-_interpolatedPosition.x, -_interpolatedPosition.y, 0.0f);
      _cameraMatrix = glm::translate(_cameraMatrix, translation);

      // apply scaling and zooming factors
      glm::vec3 zoom(_zoom, _zoom, 0.0f);
      _cameraMatrix = glm::scale(_cameraMatrix, zoom);

      _doUpdate = false;
    }
  }

  void Camera2D::resetInterpolation() {
    _previousPosition = _position;
  }

  void Camera2D::interpolate(float timestepAccumulatorRatio, bool isGamePaused) {
    if(isGamePaused) {
      setInterpolatedPosition(_position);
    } else {
      const float oneMinusRatio = 1.f - timestepAccumulatorRatio;
      glm::vec2 interpolatedCameraPosition = timestepAccumulatorRatio * _position + oneMinusRatio * _previousPosition;
      setInterpolatedPosition(interpolatedCameraPosition);
    }
  }

  //get the camera size within the world
  glm::vec2 Camera2D::getWorldViewportSize() const {
    return glm::vec2(((float) _screenWidth / _zoom) / _scale, ((float) _screenHeight / _zoom) / _scale);
  }

  glm::vec2 Camera2D::getViewportSize() const {
    return glm::vec2((float) _screenWidth / _zoom, (float) _screenHeight / _zoom);
  }

  glm::vec2 Camera2D::getPosition() {
    return _position;
  }

  glm::vec2 Camera2D::getWorldCoordinates(const glm::vec2& screenCoordinates) const {
	  return screenCoordinates / _scale;
  }

  glm::vec2 Camera2D::getScreenCoordinates(const glm::vec2& worldCoordinates) const {
	  return worldCoordinates * _scale;
  }

  float Camera2D::getWorldScalar(float screenScalar) const {
	  return screenScalar / _scale;
  }

  float Camera2D::getScreenScalar(float worldScalar) const {
	  return worldScalar * _scale;
  }

}