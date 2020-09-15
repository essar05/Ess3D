#pragma once

#include "definitions.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Ess3D {
  class API Camera2D {
    public:
      Camera2D();
      ~Camera2D();

      void init(int screenWidth, int screenHeight, float cameraWidth);

      void update();

      void setPosition(const glm::vec2& position) {
        _position = position;
        _doUpdate = true;
      }

      void setInterpolatedPosition(const glm::vec2& interpolatedPosition);

      void setZoom(float zoom) {
        _zoom = zoom;
        _doUpdate = true;
      }

      void resetInterpolation();
      void interpolate(float timestepAccumulatorRatio, bool isGamePaused);

      glm::vec2 getPosition();

      glm::vec2 getPreviousPosition() { return _previousPosition; }

      glm::vec2 getInterpolatedPosition() { return _interpolatedPosition; }

      float getScale() const { return _scale; }

      float getZoom() const { return _zoom; }

      glm::vec2 getWorldViewportSize() const;
      glm::vec2 getViewportSize() const;

      glm::vec2 getWorldCoordinates(const glm::vec2& screenCoordinates) const;
      glm::vec2 getScreenCoordinates(const glm::vec2& worldCoordinates) const;
      float getWorldScalar(float screenScalar) const;
      float getScreenScalar(float worldScalar) const;

      glm::mat4 getCameraMatrix() { return _cameraMatrix; }

    private:
      // the size of the screen in pixels
      int _screenWidth;
      int _screenHeight;

      // the size of the camera in world units
      float _width{};
      float _height{};

      bool _doUpdate;

      // defines the ratio of a world unit to screen pixels
      float _scale;
      // zooming factor of the camera
      float _zoom{};

      glm::vec2 _previousPosition;
      glm::vec2 _position;
      // the interpolated position is the one that actually gets rendered. it is a smoothed state between the previous and the desired position (based on how much time actually passed)
      glm::vec2 _interpolatedPosition;

      glm::mat4 _cameraMatrix;
      glm::mat4 _orthoMatrix;
  };
}