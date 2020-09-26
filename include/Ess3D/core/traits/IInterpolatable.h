#pragma once

#include <Ess3D/definitions.h>

class API IInterpolatable {
  public:
    virtual void interpolate(float timestepAccumulatorRatio) = 0;
    virtual void resetInterpolation() = 0;

  protected:

};