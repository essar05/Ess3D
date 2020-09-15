#pragma once

#include <definitions.h>

namespace Ess3D {

  class InputManager;

  class API IHandlesInput {
    public:
      virtual void input(InputManager* inputManager) = 0;

    protected:
      virtual void onInput(InputManager* inputManager);

  };

}