#pragma once
#include "Texture2D.h"
#include <string>

namespace Ess3D {

  class IOManager
  {
    public:
      static Texture2D loadTextureFromImage(std::string filePath);
  };

}