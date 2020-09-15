#pragma once

#include "definitions.h"

class API IUpdatable {
  public:
    virtual bool update(float deltaTime) = 0;

  protected:
    virtual bool onUpdate(float deltaTime);

};