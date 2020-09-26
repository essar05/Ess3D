#include <Ess3D/2d/rendering/Renderer2D.h>
#include <Ess3D/core/Config.h>
#include <Ess3D/core/State.h>
#include <Ess3D/2d/Scene2D.h>

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
    _finalFBO = new Ess3D::FrameBufferObject(state->getWindow().get(), (GLsizei) config->getWidth(), (GLsizei) config->getHeight(), Ess3D::DepthBufferType::TEXTURE);
    _intermediateFBO = new Ess3D::FrameBufferObject(state->getWindow().get(), (GLsizei) config->getWidth(), (GLsizei) config->getHeight(), Ess3D::DepthBufferType::TEXTURE);
  }

  Renderer2D::~Renderer2D() {
    delete _baseShader;
    delete _spriteBatch;
  }

  void Renderer2D::render(Scene2D* scene) {
    glDisable(GL_SCISSOR_TEST);
    glClearDepth(1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _baseShader->use();

    // pass the GL_TEXTURE0 location to the fragment shader as a uniform sampler
    GLint textureSamplerUniformID = _baseShader->getUniformLocation("textureSampler");
    glUniform1i(textureSamplerUniformID, 0);

    // set the useTexture shader uniform to 1
    GLint useTextureUniformID = _baseShader->getUniformLocation("useTexture");
    glUniform1i(useTextureUniformID, 1);

    GLint projectionMatrixUniformID = _baseShader->getUniformLocation("P");
    glm::mat4 cameraMatrix = scene->getCamera()->getCameraMatrix();

    glUniformMatrix4fv(projectionMatrixUniformID, 1, GL_FALSE, &(cameraMatrix[0][0]));

    //bind FBO, all rendering will be done to this FBO's color buffer
    _intermediateFBO->bind();

    // clear fbo
    glClearColor(0.00f, 0.00f, 0.00f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _spriteBatch->begin(Ess3D::GlyphSortType::BACK_TO_FRONT);

    /**
     * In fact, here we are mostly adding sprites to the render queue
     * The sprites will be efficiently rendered later
     * Any actual GL rendering will be done to the _intermediateFBO buffer
     * We will then render the sprites and the _intermediateFBO over them
     */
    scene->onRender(this);

    _spriteBatch->end();

    //unbind FBO, rendering will now be done to screen
    _intermediateFBO->unbind();

    _finalFBO->bind();

    // clear fbo
    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // RENDER THE SPRITES
    this->enableTexture();
    _spriteBatch->render();

    _baseShader->unuse();

    // RENDER WHAT HAD BEEN PREVIOUSLY DRAWN OVER THE SPRITES
    _fboRenderer->render(_intermediateFBO);

    _finalFBO->unbind();

    // TODO: APPLY POST NOW

    // clear screen buffer
    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // RENDER FINAL IMAGE
    _fboRenderer->render(_finalFBO);
  }

  void Renderer2D::addToRenderQueue(const Ess3D::Sprite& sprite) {
    _spriteBatch->addToQueue(sprite);
  }

  SpriteBatch *Renderer2D::getSpriteBatch() {
    return this->_spriteBatch;
  }

  Shader *Renderer2D::getBaseShader() {
    return this->_baseShader;
  }

  void Renderer2D::enableTexture() {
    GLint useTextureUniformID = this->_baseShader->getUniformLocation("useTexture");
    glUniform1i(useTextureUniformID, 1);
  }

  void Renderer2D::disableTexture() {
    GLint useTextureUniformID = this->_baseShader->getUniformLocation("useTexture");
    glUniform1i(useTextureUniformID, 0);
  }

}