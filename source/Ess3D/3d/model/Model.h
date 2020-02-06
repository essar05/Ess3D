#pragma once

#include <gl/Shader.h>
#include <vector>
#include "Mesh.h"

namespace Ess3D {
  class Model {
    public:
      void render(Shader* shader);
      void initialize();

      void addMesh(Mesh* mesh);

    private:
      std::vector<Mesh*> _meshes;
  };
}
