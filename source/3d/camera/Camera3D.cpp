#include <Ess3D/3d/camera/Camera3D.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Ess3D {

  Camera3D::Camera3D(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch) {
    this->_position = position;
    this->_worldUp = worldUp;
    this->_yaw = yaw;
    this->_pitch = pitch;
    updateVectors();
  }

  Camera3D::~Camera3D() { }

  void Camera3D::moveForward() {
    this->_position += this->_speed * this->_front;
  }

  void Camera3D::moveBackward() {
    this->_position -= this->_speed * this->_front;
  }

  void Camera3D::moveLeft() {
    this->_position -= this->_speed * this->_right;
  }

  void Camera3D::moveRight() {
    this->_position += this->_speed * this->_right;
  }

  void Camera3D::look(glm::vec2 delta) {
    this->_yaw += delta.x * this->_sensitivity;
    this->_pitch -= delta.y * this->_sensitivity;

    if (this->_pitch > 89.0f) {
      _pitch = 89.0f;
    }

    if (this->_pitch < -89.0f) {
      this->_pitch = -89.0f;
    }

    updateVectors();
  }

  glm::mat4 Camera3D::getViewMatrix() {
    return glm::lookAt(this->_position, this->_position + this->_front, this->_up);
  }

  void Camera3D::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    front.y = sin(glm::radians(this->_pitch));
    front.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    this->_front = glm::normalize(front);

    this->_right = glm::normalize(glm::cross(this->_front, this->_worldUp));
    this->_up = glm::normalize(glm::cross(this->_right, this->_front));
  }

}