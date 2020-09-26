#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/3d/rendering/MeshRenderer.h>
#include <Ess3D/3d/model/Vertex3D.h>
#include <Ess3D/resources/Texture.h>
#include <vector>

namespace Ess3D {
  class MeshRenderer;

  class API Mesh {
    public:
      Mesh();
      ~Mesh();

      const std::vector<Vertex3D>& getVertices();
      const std::vector<unsigned int>& getIndices();
      const std::vector<Texture*>& getTextures();

      void addVertex(const Vertex3D& vertex);
      void addIndex(unsigned int index);
      void addTexture(Texture* texture);

      MeshRenderer* getMeshRenderer();

    private:
      std::vector<Vertex3D> _vertices;
      std::vector<unsigned int> _indices;
      std::vector<Texture*> _textures;

      MeshRenderer* _meshRenderer;

  };
};