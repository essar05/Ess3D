#pragma once
#include "TextureCache.h"
#include <string>

namespace Ess3D {

  class ResourceManager {
    public:
      static Texture2D getTexture(std::string texturePath);

  };

}