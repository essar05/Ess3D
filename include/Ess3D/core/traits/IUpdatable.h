#pragma once

#include <Ess3D/definitions.h>

namespace Ess3D {
  
  class API IUpdatable {
    public:
      virtual bool update(float deltaTime) = 0;

    protected:
      virtual bool onUpdate(float deltaTime);

  };

}