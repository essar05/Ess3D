#ifndef DAPOLIS_PONG_IDRAWABLE2D_H
#define DAPOLIS_PONG_IDRAWABLE2D_H

#include <2d/rendering/Renderer2D.h>

namespace Ess3D {

  class API IDrawable2D {
    public:
      virtual void draw(Renderer2D *renderer) = 0;

  };

}

#endif
