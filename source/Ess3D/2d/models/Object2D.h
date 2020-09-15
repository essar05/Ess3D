#pragma once

#include "definitions.h"
#include "2d/traits/IRenderable2D.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <gl/ColorRGBA8.h>
#include <core/traits/IInterpolatable.h>
#include <core/traits/IUpdatable.h>
#include <core/traits/IHandlesInput.h>

namespace Ess3D {
  class API Object2D: public IUpdatable, public IRenderable2D, public IHandlesInput, public IInterpolatable {
    public:

      Object2D();
      Object2D(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv);
      Object2D(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv, Ess3D::ColorRGBA8 color);

      bool update(float deltaTime) final;
      void input(InputManager *inputManager) final;
      void render(Renderer2D *renderer) final;

      void interpolate(float timestepAccumulatorRatio) override;
      void resetInterpolation() override;

      GLuint getTextureId() const;
      void setTextureId(GLuint textureId);

      glm::vec4 getUV();
      void setUV(const glm::vec4& uv);

      Ess3D::ColorRGBA8 getColor();
      void setColor(Ess3D::ColorRGBA8 color);

      glm::vec2 getSize();
      void setSize(const glm::vec2& size);

      glm::vec2 getPreviousPosition();
      void setPreviousPosition(const glm::vec2& previousPosition);

      glm::vec2 getPosition();
      void setPosition(const glm::vec2& position);

      glm::vec2 getInterpolatedPosition();
      void setInterpolatedPosition(const glm::vec2& interpolatedPosition);

    protected:
      bool onUpdate(float deltaTime) override;
      void onRender(Renderer2D *renderer) override;

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
