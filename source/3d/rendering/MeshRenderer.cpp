#include <Ess3D/3d/rendering/MeshRenderer.h>
#include <iostream>

const unsigned int MAX_DIFFUSE_TEXTURES = 5;
const unsigned int MAX_SPECULAR_TEXTURES = 5;
const unsigned int MAX_HEIGHT_TEXTURES = 3;
const unsigned int MAX_NORMAL_TEXTURES = 3;

namespace Ess3D {
  MeshRenderer::MeshRenderer() : MeshRenderer(nullptr) {}

  MeshRenderer::MeshRenderer(Mesh* mesh) : _mesh(mesh) {}

  void MeshRenderer::render(Shader* shader) {
    int textureDiffuseCount = 0;
    int textureSpecularCount = 0;
    int textureHeightCount = 0;
    int textureNormalCount = 0;

    MeshRenderer::resetUseTextureFlags(shader);

    for (unsigned int textureIndex = 0; textureIndex < _mesh->getTextures().size(); textureIndex++) {
      Texture* texture = _mesh->getTextures()[textureIndex];

      glActiveTexture(GL_TEXTURE0 + textureIndex);

      std::string samplerUniformName = "material_";

      switch (texture->getType()) {
        case ESS_TEX_TYPE_DIFFUSE:
          samplerUniformName = MeshRenderer::getUniformSamplerName(texture->getType(), ++textureDiffuseCount);
          break;
        case ESS_TEX_TYPE_SPECULAR:
          samplerUniformName = MeshRenderer::getUniformSamplerName(texture->getType(), ++textureSpecularCount);
          break;
        case ESS_TEX_TYPE_HEIGHT:
          samplerUniformName = MeshRenderer::getUniformSamplerName(texture->getType(), ++textureHeightCount);
          break;
        case ESS_TEX_TYPE_NORMAL:
          samplerUniformName = MeshRenderer::getUniformSamplerName(texture->getType(), ++textureNormalCount);
          break;
      }

      glUniform1i(shader->getUniformLocation("use_" + samplerUniformName), 1);
      glUniform1i(shader->getUniformLocation(samplerUniformName), textureIndex);
      glBindTexture(GL_TEXTURE_2D, texture->getId());
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void MeshRenderer::initialize() {
    this->initializeGLBuffers();
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*) 0);

    // in vec3 normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*) offsetof(Vertex3D, normal));

    // in vec2 uv
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*) offsetof(Vertex3D, uv));

    glBindVertexArray(0);
  }

  void MeshRenderer::resetUseTextureFlags(Shader* shader) {
    for (unsigned int textureCount = 1; textureCount <= MAX_DIFFUSE_TEXTURES; textureCount++) {
      glUniform1i(shader->getUniformLocation("use_" + MeshRenderer::getUniformSamplerName(ESS_TEX_TYPE_DIFFUSE, textureCount) ), 0);
    }

    for (unsigned int textureCount = 1; textureCount <= MAX_SPECULAR_TEXTURES; textureCount++) {
      glUniform1i(shader->getUniformLocation("use_" + MeshRenderer::getUniformSamplerName(ESS_TEX_TYPE_SPECULAR, textureCount) ), 0);
    }

    for (unsigned int textureCount = 1; textureCount <= MAX_HEIGHT_TEXTURES; textureCount++) {
      glUniform1i(shader->getUniformLocation("use_" + MeshRenderer::getUniformSamplerName(ESS_TEX_TYPE_HEIGHT, textureCount) ), 0);
    }

    for (unsigned int textureCount = 1; textureCount <= MAX_NORMAL_TEXTURES; textureCount++) {
      glUniform1i(shader->getUniformLocation("use_" + MeshRenderer::getUniformSamplerName(ESS_TEX_TYPE_NORMAL, textureCount) ), 0);
    }
  }

  std::string MeshRenderer::getUniformSamplerName( TextureType textureType, unsigned int index ) {
    std::string samplerUniformName = "material_";

    switch (textureType) {
      case ESS_TEX_TYPE_DIFFUSE:
        samplerUniformName += "texDiffuse" + std::to_string(index);
        break;
      case ESS_TEX_TYPE_SPECULAR:
        samplerUniformName += "texSpecular" + std::to_string(index);
        break;
      case ESS_TEX_TYPE_HEIGHT:
        samplerUniformName += "texHeight" + std::to_string(index);
        break;
      case ESS_TEX_TYPE_NORMAL:
        samplerUniformName += "texNormal" + std::to_string(index);
        break;
      case ESS_TEX_TYPE_NONE:
        break;
    }

    return samplerUniformName;
  }

}