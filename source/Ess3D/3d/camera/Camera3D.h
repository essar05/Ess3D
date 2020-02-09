#pragma once

#include "definitions.h"
#include <glm/glm.hpp>

namespace Ess3D {

  class API Camera3D {
    private:
      glm::vec3 _position;
      glm::vec3 _front;
      glm::vec3 _up;
      glm::vec3 _right;
      glm::vec3 _worldUp;

      float _yaw;
      float _pitch;

      float _speed = 0.1f;
      float _sensitivity = 0.01f;

      void updateVectors();

    public:
      Camera3D(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = -90.0f, float pitch = 0.0f);
      ~Camera3D();

      void moveForward();
      void moveBackward();
      void moveLeft();
      void moveRight();
      void look(glm::vec2 delta);
      glm::mat4 getViewMatrix();

  };

}