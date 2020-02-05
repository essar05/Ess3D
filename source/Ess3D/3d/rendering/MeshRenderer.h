#pragma once

#include "3d/model/Mesh.h"

namespace Ess3D {
  class Mesh;

  class MeshRenderer {
    public:
      MeshRenderer();
      explicit MeshRenderer(Mesh* mesh);

    private:
      Mesh* mesh;
  };
};