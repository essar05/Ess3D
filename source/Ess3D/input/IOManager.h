#pragma once
#include "2d/textures/Texture2D.h"
#include <string>

namespace Ess3D {

  class IOManager
  {
    public:
      static Texture2D loadTextureFromImage(std::string filePath);
  };

}