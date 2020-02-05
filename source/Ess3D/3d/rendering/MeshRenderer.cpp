#include "MeshRenderer.h"

Ess3D::MeshRenderer::MeshRenderer() : MeshRenderer(nullptr) {}

Ess3D::MeshRenderer::MeshRenderer(Ess3D::Mesh* mesh) {
  this->mesh = mesh;
}