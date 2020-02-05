#pragma once

#include <vector>
#include "3d/rendering/MeshRenderer.h"
#include "Vertex3D.h"
#include "Texture3D.h"

namespace Ess3D {
  class MeshRenderer;

  class Mesh {
    public:
      std::vector<Vertex3D> vertices;
      std::vector<unsigned int> indices;
      std::vector<Texture3D> textures;
      MeshRenderer* meshRenderer;

      Mesh(const std::vector<Vertex3D>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<Texture3D>& textures);
      ~Mesh();
  };
};