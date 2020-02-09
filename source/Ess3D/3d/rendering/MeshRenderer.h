#pragma once

#include "definitions.h"
#include <gl/Shader.h>
#include "3d/model/Mesh.h"

namespace Ess3D {
  class Mesh;

  class API MeshRenderer {
    public:
      MeshRenderer();
      explicit MeshRenderer(Mesh* mesh);

      void render(Shader* shader);
      void initialize();

    private:
      Mesh* _mesh;

      unsigned int _VAO{}, _VBO{}, _EBO{};
      void initializeGLBuffers();
  };
};