#pragma once

#include <gl/Shader.h>
#include <gl/FBORenderer.h>
#include "SpriteBatch.h"

namespace Ess3D {

  class Scene2D;

  class API Renderer2D {
    public:
      Renderer2D();
      virtual ~Renderer2D();

      virtual void render(Scene2D* scene);

      virtual void drawQuad(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureId, const ColorRGBA8& color, float zDepth, float angle);

      SpriteBatch* getSpriteBatch();
      Shader* getBaseShader();

    protected:
      Shader* _baseShader;
      SpriteBatch* _spriteBatch;
      FrameBufferObject* _fbo;
      FBORenderer* _fboRenderer;
  };

}