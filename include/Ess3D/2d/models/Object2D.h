#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/2d/traits/IRenderable2D.h>
#include <Ess3D/gl/ColorRGBA8.h>
#include <Ess3D/core/traits/IInterpolatable.h>
#include <Ess3D/core/traits/IUpdatable.h>
#include <Ess3D/core/traits/IHandlesInput.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/trigonometric.hpp>
#include <GL/glew.h>

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

      float getAngle();
      void setAngle(float angle);

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

      float _angle = glm::radians(0.f);

  };

}
