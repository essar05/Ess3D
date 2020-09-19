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

      virtual void addToRenderQueue(const Ess3D::Sprite& sprite);

      void enableTexture();
      void disableTexture();

      SpriteBatch* getSpriteBatch();
      Shader* getBaseShader();

    protected:
      Shader* _baseShader;
      SpriteBatch* _spriteBatch;
      FrameBufferObject* _finalFBO;
      FrameBufferObject* _intermediateFBO;
      FBORenderer* _fboRenderer;
  };

}