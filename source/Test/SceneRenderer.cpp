#include "SceneRenderer.h"
#include "Game.h"
#include <2d/textures/TextureCache.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SceneRenderer::SceneRenderer() {}

SceneRenderer::SceneRenderer(float _width, float _height) {
  this->_width = _width;
  this->_height = _height;

  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

  _shader = new Ess3D::Shader(true);

  _shader->loadShader(Ess3D::ShaderType::VERTEX, "Shaders/Base3D.vertex.shader");
  _shader->loadShader(Ess3D::ShaderType::FRAGMENT, "Shaders/Base3D.frag.shader");
  _shader->compileShaders();

  _shader->addAttribute("vertexPosition");
  //_shader->addAttribute("vertexColor");
  _shader->addAttribute("vertexUV");
  _shader->linkShaders();

  _camera = new Ess3D::Camera3D(glm::vec3(0.0f, 0.0f, 3.0f));

  glEnable(GL_DEPTH_TEST);

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  //glEnableVertexAttribArray(2);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
  //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)) );
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)) );

  glBindVertexArray(0);

  //preload texture
  _textureId = Ess3D::TextureCache::getInstance()->getTexture("Textures/Background/Background_Tilable.png")._id;
}

SceneRenderer::~SceneRenderer() {
  delete _shader;
  delete _camera;
}

void SceneRenderer::render() {
  Game* game = Game::GetInstance();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  _shader->use();

  glBindVertexArray(_vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _textureId);
  glUniform1i(_shader->getUniformLocation("textureSampler"), 0);

  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;
  
  model = glm::rotate(model, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));
  view = _camera->getViewMatrix();
  projection = glm::perspective(45.0f, _width / _height, 1.0f, 50.0f);

  glUniformMatrix4fv(_shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(_shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(_shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

  glDrawArrays(GL_TRIANGLES, 0, 36);

  _shader->unuse();
}

Ess3D::Camera3D* SceneRenderer::getCamera() {
  return this->_camera;
}