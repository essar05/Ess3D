#include "MeshRenderer.h"

namespace Ess3D {
  MeshRenderer::MeshRenderer() : MeshRenderer(nullptr) {}

  MeshRenderer::MeshRenderer(Mesh* mesh) : _mesh(mesh) {
    this->initializeGLBuffers();
  }

  void MeshRenderer::render(Shader* shader) {
    int textureDiffuseCount = 0;
    int textureSpecularCount = 0;

    for (int i = 0; i < _mesh->getTextures().size(); i++) {
      Texture* texture = _mesh->getTextures()[i];

      glActiveTexture(GL_TEXTURE0 + i);

      std::string samplerUniformName = "material.";

      switch (texture->getType()) {
        case DIFFUSE:
          samplerUniformName += "texture_diffuse" + std::to_string(++textureDiffuseCount);
          break;
        case SPECULAR:
          samplerUniformName += "texture_specular" + std::to_string(++textureSpecularCount);
          break;
      }

      glUniform1i(shader->getUniformLocation(samplerUniformName), i);
      glBindTexture(GL_TEXTURE_2D, texture->getId());
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void MeshRenderer::initializeGLBuffers() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        _mesh->getVertices().size() * sizeof(Vertex3D),
        _mesh->getVertices().data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        _mesh->getIndices().size() * sizeof(unsigned int),
        _mesh->getIndices().data(),
        GL_STATIC_DRAW
    );

    // in vec3 position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*) offsetof(Vertex3D, position));

    // in vec3 normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*) offsetof(Vertex3D, normal));

    // in vec2 uv
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*) offsetof(Vertex3D, uv));

    glBindVertexArray(0);
  }

}