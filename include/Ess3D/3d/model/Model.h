#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/gl/Shader.h>
#include <Ess3D/3d/model/Mesh.h>
#include <utility>
#include <vector>

namespace Ess3D {
  class API Model {
    public:
      explicit Model(std::string  id) : _id(std::move(id)) {}

      void render(Shader* shader);
      void initialize();

      void addMesh(Mesh* mesh);

    private:
      std::string _id;
      std::vector<Mesh*> _meshes;


  };
}
