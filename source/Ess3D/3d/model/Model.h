#pragma once

#include "definitions.h"
#include <gl/Shader.h>
#include <vector>
#include "Mesh.h"

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
