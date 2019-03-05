#pragma once
#include <Shader.h>
#include <glm/glm.hpp>

class SceneRenderer {
  public:
    SceneRenderer();
    SceneRenderer(float _width, float _height);
    ~SceneRenderer();

    void render();

  private:
    Ess3D::Shader* _shader;
	  GLuint _vao;
	  GLuint _vbo;
	  GLuint _ebo;

    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;

    float _width;
    float _height;
	  int _textureId;
	  int _textureId2;

};

