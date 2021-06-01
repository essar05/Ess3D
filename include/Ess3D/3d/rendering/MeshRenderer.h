#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/gl/Shader.h>
#include <Ess3D/3d/model/Mesh.h>
#include <Ess3D/resources/Texture.h>

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
      static void resetUseTextureFlags(Shader* shader);

      static std::string getUniformSamplerName(TextureType textureType, unsigned int index) ;
  };
};