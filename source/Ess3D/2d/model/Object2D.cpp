#pragma once

#include "Object2D.h"

namespace Ess3D {

    Object2D::Object2D() = default;

    Object2D::Object2D(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
        Object2D(position, size, textureId, uv, Ess3D::ColorRGBA8(225, 255, 255, 255)) {}

    Object2D::Object2D(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv, Ess3D::ColorRGBA8 color) {
      setPosition(position);
      setSize(size);
      setTextureId(textureId);
      setUV(uv);
      setColor(color);
    }
}
