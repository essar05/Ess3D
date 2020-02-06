#include "Mesh.h"

namespace Ess3D {
  Mesh::Mesh(
      const std::vector<Vertex3D>& vertices,
      const std::vector<unsigned int>& indices,
      const std::vector<Texture*>& textures
  ) : _vertices(vertices), _indices(indices), _textures(textures) {
    _meshRenderer = new MeshRenderer(this);
  }

  Mesh::~Mesh() {
    delete _meshRenderer;
  }

  const std::vector<Vertex3D>& Mesh::getVertices() {
    return _vertices;
  }

  const std::vector<unsigned int>& Mesh::getIndices() {
    return _indices;
  }

  const std::vector<Texture*>& Mesh::getTextures() {
    return _textures;
  }

  MeshRenderer* Mesh::getMeshRenderer() {
    return _meshRenderer;
  }
}