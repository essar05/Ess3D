#include <Ess3D/3d/model/Mesh.h>

namespace Ess3D {
  Mesh::Mesh() {
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

  void Mesh::addVertex(const Vertex3D& vertex) {
    _vertices.push_back(vertex);
  }

  void Mesh::addIndex(unsigned int index) {
    _indices.push_back(index);
  }

  void Mesh::addTexture(Texture* texture) {
    _textures.push_back(texture);
  }

  MeshRenderer* Mesh::getMeshRenderer() {
    return _meshRenderer;
  }
}