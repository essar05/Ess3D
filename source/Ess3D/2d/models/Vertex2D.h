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
      Glyph() {}

      Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint TextureId, const ColorRGBA8& color, float ZDepth,
            float angle = 0) : textureId(TextureId), zDepth(ZDepth) {
        glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

        // Get points centered at origin
        glm::vec2 tl(-halfDims.x, halfDims.y);
        glm::vec2 bl(-halfDims.x, -halfDims.y);
        glm::vec2 br(halfDims.x, -halfDims.y);
        glm::vec2 tr(halfDims.x, halfDims.y);

      // Rotate the points
      tl = rotatePoint(tl, angle) + halfDims;
      bl = rotatePoint(bl, angle) + halfDims;
      br = rotatePoint(br, angle) + halfDims;
      tr = rotatePoint(tr, angle) + halfDims;

      topLeft.color = color;
      topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
      topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

      bottomLeft.color = color;
      bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
      bottomLeft.setUV(uvRect.x, uvRect.y);

      bottomRight.color = color;
      bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
      bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

      topRight.color = color;
      topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
      topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }

      glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle) {
        glm::vec2 newv;
        newv.x = pos.x * cos(angle) - pos.y * sin(angle);
        newv.y = pos.x * sin(angle) + pos.y * cos(angle);
        return newv;
      }

      GLuint textureId;
      float zDepth;

      Vertex2D topLeft;
      Vertex2D bottomLeft;
      Vertex2D topRight;
      Vertex2D bottomRight;
  };

}

