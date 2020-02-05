#include "Mesh.h"

Ess3D::Mesh::Mesh(
    const std::vector<Vertex3D>& vertices,
    const std::vector<unsigned int>& indices,
    const std::vector<Texture3D>& textures
) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  this->meshRenderer = new MeshRenderer(this);
}

Ess3D::Mesh::~Mesh() {
  delete this->meshRenderer;
}
