#pragma once

#include <gl/Shader.h>
#include <3d/camera/Camera3D.h>
#include <glm/glm.hpp>

class SceneRenderer {
  public:
    SceneRenderer();
    SceneRenderer(float _width, float _height);
    ~SceneRenderer();

    void render();
    Ess3D::Camera3D* getCamera();

  private:
    Ess3D::Shader* _shader;
    Ess3D::Camera3D* _camera;

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

