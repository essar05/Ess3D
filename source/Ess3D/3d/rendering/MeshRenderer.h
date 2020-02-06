#pragma once

#include <gl/Shader.h>
#include "3d/model/Mesh.h"

namespace Ess3D {
  class Mesh;

  class MeshRenderer {
    public:
      MeshRenderer();
      explicit MeshRenderer(Mesh* mesh);

      void render(Shader* shader);

    private:
      Mesh* _mesh;

      unsigned int _VAO{}, _VBO{}, _EBO{};
      void initializeGLBuffers();
  };
};