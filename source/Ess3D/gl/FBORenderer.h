#pragma once

#include "definitions.h"
#include <gl/Shader.h>
#include <gl/FrameBufferObject.h>

namespace Ess3D {
  class API FBORenderer {
    public:
      FBORenderer();
      ~FBORenderer();

      virtual void render(FrameBufferObject* fbo);
      virtual void initShader();
      void drawFullscreenQuad(GLuint textureId);

    protected:
      virtual void initVertexAttributeObject();

      Shader* _shader;
      GLuint _vao;
      GLuint _vbo;

  };
}

