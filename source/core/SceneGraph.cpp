#include <Ess3D/core/SceneGraph.h>

namespace Ess3D {

  template<typename Entity>
  SceneGraph<Entity>::SceneGraph() = default;

  template<typename Entity>
  SceneGraph<Entity>::~SceneGraph() = default;

  template<typename Entity>
  uint32_t SceneGraph<Entity>::addEntity( std::unique_ptr<Entity> entity ) {
    _entities[_entityCount++] = entity;
    return _entityCount - 1;
  }

  template<typename Entity>
  Entity* SceneGraph<Entity>::getEntity( uint32_t id ) {
    auto it = _entities.find(id);
    if(it == _entities.end()) {
      return nullptr;
    }
    return it->second.get();
  }

  template<typename Entity>
  void SceneGraph<Entity>::deleteEntity( uint32_t id ) {
    auto it = _entities.find(id);
    if(it != _entities.end()) {

      delete it->second;
      _entities.erase(it);
    }
  }

}