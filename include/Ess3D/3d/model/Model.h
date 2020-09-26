#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/gl/Shader.h>
#include <Ess3D/3d/model/Mesh.h>
#include <vector>

namespace Ess3D {
  class API Model {
    public:
      void render(Shader* shader);
      void initialize();

      void addMesh(Mesh* mesh);

    private:
      std::vector<Mesh*> _meshes;
  };
}
