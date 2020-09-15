#include "Renderer2D.h"
#include <core/Config.h>
#include <core/State.h>
#include <2d/Scene2D.h>

namespace Ess3D {

  Renderer2D::Renderer2D() {
    State* state = State::get();
    Config* config = Config::get();

    _baseShader = new Ess3D::Shader(true);

    _baseShader->loadShader(Ess3D::ShaderType::VERTEX, "shaders/2D.vs");
    _baseShader->loadShader(Ess3D::ShaderType::FRAGMENT, "shaders/2D.fs");
    _baseShader->compileShaders();

    _baseShader->addAttribute("vertexPosition");
    _baseShader->addAttribute("vertexColor");
    _baseShader->addAttribute("vertexUV");

    _baseShader->linkShaders();

    _spriteBatch = new Ess3D::SpriteBatch();
    _spriteBatch->init();

    _fboRenderer = new FBORenderer();
    _fboRenderer->initShader();
    _fbo = new Ess3D::FrameBufferObject(state->getWindow().get(), (GLsizei) config->getWidth(), (GLsizei) config->getHeight(), Ess3D::DepthBufferType::TEXTURE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClearDepth(1.0);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  Renderer2D::~Renderer2D() {
    delete _baseShader;
    delete _spriteBatch;
  }

  void Renderer2D::render(Scene2D* scene) {
    // clear screen buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //bind FBO, all rendering will be done to this FBO's color buffer
    _fbo->bind();

    // clear fbo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _baseShader->use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureSamplerUniformID = _baseShader->getUniformLocation("textureSampler");
    glUniform1i(textureSamplerUniformID, 0);

    GLint useTextureUniformID = _baseShader->getUniformLocation("useTexture");
    glUniform1i(useTextureUniformID, 1);

    GLint projectionMatrixUniformID = _baseShader->getUniformLocation("P");
    glm::mat4 cameraMatrix = scene->getCamera()->getCameraMatrix();

    glUniformMatrix4fv(projectionMatrixUniformID, 1, GL_FALSE, &(cameraMatrix[0][0]));

    _spriteBatch->begin(Ess3D::GlyphSortType::BACK_TO_FRONT);

    // render the scene
    scene->onRender(this);

    _spriteBatch->end();
    _spriteBatch->render();

    _baseShader->unuse();

    //apply POST

    //unbind FBO, rendering will now be done to screen
    _fbo->unbind();

    _fboRenderer->render(_fbo);
  }

  SpriteBatch *Renderer2D::getSpriteBatch() {
    return this->_spriteBatch;
  }

  void Renderer2D::drawQuad(
    const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint textureId,
    const ColorRGBA8 &color, float zDepth, float angle
  ) {
    _spriteBatch->draw(destRect, uvRect, textureId, color, zDepth, angle);
  }

}