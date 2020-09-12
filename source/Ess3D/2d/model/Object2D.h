#pragma once

#include "definitions.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <gl/ColorRGBA8.h>

namespace Ess3D {
  class API Object2D {
    public:

      Object2D();
      Object2D(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv);
      Object2D(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv, Ess3D::ColorRGBA8 color);

      virtual void draw() = 0;
      virtual bool update(float deltaTime) = 0;

      virtual void interpolate(float timestepAccumulatorRatio) = 0;
      virtual void resetInterpolation() = 0;

      GLuint getTextureId() const {
        return this->_textureId;
      }

      void setTextureId(GLuint textureId) {
        this->_textureId = textureId;
      }

      glm::vec4 getUV() {
        return this->_uv;
      }

      void setUV(const glm::vec4& uv) {
        this->_uv = uv;
      }

      Ess3D::ColorRGBA8 getColor() {
        return this->_color;
      }

      void setColor(Ess3D::ColorRGBA8 color) {
        this->_color = color;
      }

      glm::vec2 getSize() {
        return this->_size;
      }

      void setSize(const glm::vec2& size) {
        this->_size = size;
      }

      glm::vec2 getPreviousPosition() {
        return this->_previousPosition;
      }

      void setPreviousPosition(const glm::vec2& previousPosition) {
        this->_previousPosition = previousPosition;
      }

      glm::vec2 getPosition() {
        return this->_position;
      }

      void setPosition(const glm::vec2& position) {
        this->_position = position;
      }

      glm::vec2 getInterpolatedPosition() {
        return this->_interpolatedPosition;
      }

      void setInterpolatedPosition(const glm::vec2& interpolatedPosition) {
        this->_interpolatedPosition = interpolatedPosition;
      }

    protected:

      // render information
      GLuint _textureId{};
      glm::vec4 _uv;
      Ess3D::ColorRGBA8 _color;

      glm::vec2 _size;

      glm::vec2 _previousPosition;
      glm::vec2 _position;
      // only used for rendering
      glm::vec2 _interpolatedPosition;

  };

}
