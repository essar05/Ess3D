#pragma once
#include "2d/model/Texture2D.h"
#include <string>

namespace Ess3D {

  class IOManager
  {
    public:
      static Texture2D loadTextureFromImage(std::string filePath);
  };

}