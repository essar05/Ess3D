#pragma once

#include <definitions.h>

namespace Ess3D {

  class Renderer2D;

  class API IRenderable2D {
    public:
      virtual void render(Renderer2D *renderer) = 0;

    protected:
      virtual void onRender(Renderer2D *renderer);
      virtual void onRenderingDone(Renderer2D *renderer);

  };

}