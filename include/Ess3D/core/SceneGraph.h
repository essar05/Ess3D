#pragma once

#include <cstdint>
#include <unordered_map>
#include <Ess3D/2d/models/Entity2D.h>

namespace Ess3D {

  template <typename Entity>
  class SceneGraph {
    public:
      SceneGraph();
      ~SceneGraph();

      uint32_t addEntity(std::unique_ptr<Entity> entity);
      Entity* getEntity(uint32_t id);
      void deleteEntity(uint32_t id);

    protected:
      std::unordered_map<uint32_t, std::unique_ptr<Entity>> _entities;
      uint32_t _entityCount = 0;

  };

}