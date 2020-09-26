#include <Ess3D/gl/FBORenderer.h>
#include <Ess3D/2d/models/Vertex2D.h>
#include <vector>
#include <glm/glm.hpp>

namespace Ess3D {

  FBORenderer::FBORenderer() {
  }

  FBORenderer::~FBORenderer() {
    delete _shader;
  }

  void FBORenderer::initShader() {
    _shader = new Shader(false);

    _shader->loadShader(ShaderType::VERTEX, "shaders/FBO.vs");
    _shader->loadShader(ShaderType::FRAGMENT, "shaders/FBO.fs");
    _shader->compileShaders();

    _shader->addAttribute("vertexPosition");
    _shader->addAttribute("vertexColor");
    _shader->addAttribute("vertexUV");
    _shader->linkShaders();

    initVertexAttributeObject();
  }

  void FBORenderer::initVertexAttributeObject() {
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                          (void *) offsetof(Vertex2D, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D),
                          (void *) offsetof(Vertex2D, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *) offsetof(Vertex2D, uv));

    glBindVertexArray(0);
  }

  void FBORenderer::drawFullscreenQuad(GLuint textureId) {
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _shader->getUniformLocation("textureSampler");
    glUniform1i(textureLocation, 0);

    Glyph glyph(
      glm::vec2(0.0f, 0.0f),
      glm::vec2(2.0f, 2.0f),
      glm::vec4(0.0f, 1.0f, 1.0f, -1.0f),
      textureId,
      ColorRGBA8(225, 255, 255, 255),
      0.0f
    );
    std::vector<Vertex2D> vertices;
    vertices.resize(6);
    vertices[0] = glyph.topLeftVertex;
    vertices[1] = glyph.bottomLeftVertex;
    vertices[2] = glyph.bottomRightVertex;
    vertices[3] = glyph.bottomRightVertex;
    vertices[4] = glyph.topRightVertex;
    vertices[5] = glyph.topLeftVertex;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(_vao);

    glBindTexture(GL_TEXTURE_2D, glyph.textureId);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
  }

  void FBORenderer::render(FrameBufferObject *fbo) {
    _shader->use();

    drawFullscreenQuad(fbo->getColorTextureId());

    _shader->unuse();
  }

}