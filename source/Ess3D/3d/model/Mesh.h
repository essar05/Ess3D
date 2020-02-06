#pragma once

#include <vector>
#include "3d/rendering/MeshRenderer.h"
#include "Vertex3D.h"
#include "textures/Texture.h"

namespace Ess3D {
  class MeshRenderer;

  class Mesh {
    public:
      Mesh(const std::vector<Vertex3D>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<Texture*>& textures);
      ~Mesh();

      const std::vector<Vertex3D>& getVertices();
      const std::vector<unsigned int>& getIndices();
      const std::vector<Texture*>& getTextures();

      MeshRenderer* getMeshRenderer();

    private:
      std::vector<Vertex3D> _vertices;
      std::vector<unsigned int> _indices;
      std::vector<Texture*> _textures;

      MeshRenderer* _meshRenderer;

  };
};