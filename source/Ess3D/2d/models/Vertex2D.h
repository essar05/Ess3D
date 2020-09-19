#pragma once

#include "definitions.h"
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gl/ColorRGBA8.h"
#include "gl/UV.h"

namespace Ess3D {

  struct API Position2D {
    float x;
    float y;
  };

  struct API Vertex2D {
    Position2D position{};
    ColorRGBA8 color;
    UV uv{};

    void setPosition(float x, float y) {
      position.x = x;
      position.y = y;
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
      color.r = r;
      color.g = g;
      color.b = b;
      color.a = a;
    }

    void setUV(float u, float v) {
      uv.u = u;
      uv.v = v;
    }

  };

  enum class GlyphSortType {
      NONE,
      FRONT_TO_BACK,
      BACK_TO_FRONT,
      TEXTURE
  };

  class API Glyph {
    public:
      Glyph() = default;

      Glyph(
        const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &uv,
        GLuint TextureId, const ColorRGBA8 &color, float ZDepth, float angle = 0.f
      ) : textureId(TextureId), zDepth(ZDepth) {
        glm::vec2 halfSize(size.x / 2.0f, size.y / 2.0f);

        // Get points centered at origin
        glm::vec2 topLeft(-halfSize.x, halfSize.y);
        glm::vec2 bottomLeft(-halfSize.x, -halfSize.y);
        glm::vec2 bottomRight(halfSize.x, -halfSize.y);
        glm::vec2 topRight(halfSize.x, halfSize.y);

        // Rotate the points
        topLeft = rotatePoint(topLeft, angle);
        bottomLeft = rotatePoint(bottomLeft, angle);
        bottomRight = rotatePoint(bottomRight, angle);
        topRight = rotatePoint(topRight, angle);

        this->topLeftVertex.color = color;
        this->topLeftVertex.setPosition(position.x + topLeft.x, position.y + topLeft.y);
        this->topLeftVertex.setUV(uv.x, uv.y + uv.w);

        this->bottomLeftVertex.color = color;
        this->bottomLeftVertex.setPosition(position.x + bottomLeft.x, position.y + bottomLeft.y);
        this->bottomLeftVertex.setUV(uv.x, uv.y);

        this->bottomRightVertex.color = color;
        this->bottomRightVertex.setPosition(position.x + bottomRight.x, position.y + bottomRight.y);
        this->bottomRightVertex.setUV(uv.x + uv.z, uv.y);

        this->topRightVertex.color = color;
        this->topRightVertex.setPosition(position.x + topRight.x, position.y + topRight.y);
        this->topRightVertex.setUV(uv.x + uv.z, uv.y + uv.w);
      }

      static glm::vec2 rotatePoint(const glm::vec2 &position, float angle) {
        glm::vec2 newPoint;
        newPoint.x = position.x * cos(angle) - position.y * sin(angle);
        newPoint.y = position.x * sin(angle) + position.y * cos(angle);
        return newPoint;
      }

      GLuint textureId{};
      float zDepth{};

      Vertex2D topLeftVertex;
      Vertex2D bottomLeftVertex;
      Vertex2D topRightVertex;
      Vertex2D bottomRightVertex;
  };

}

