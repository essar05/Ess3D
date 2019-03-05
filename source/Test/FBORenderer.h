#pragma once
#include <Shader.h>
#include <FrameBufferObject.h>

class FBORenderer {
  public:
    FBORenderer();
    ~FBORenderer();

    virtual void render(Ess3D::FrameBufferObject* fbo);
    virtual void initShader();
    void drawFullscreenQuad(GLuint textureId);
    
  protected:
    virtual void initVertexAttributeObject();

    Ess3D::Shader* _shader;
    GLuint _vao;
    GLuint _vbo;

};

