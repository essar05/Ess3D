#pragma once

#include "definitions.h"
#include <glm/glm.hpp>
#include <string>

namespace Ess3D {
  class API TextureAtlasSection {
    public:
      const std::string& getName() const;
      int getX() const;
      int getY() const;
      int getWidth() const;
      int getHeight() const;
      const glm::vec4& getUV() const;

      void setName(const std::string& name);
      void setX(int x);
      void setY(int y);
      void setWidth(int width);
      void setHeight(int height);

      void generateUV(int atlasWidth, int atlasHeight);

    private:
      std::string _name;
      int _x;
      int _y;
      int _width;
      int _height;
      glm::vec4 _uv;
  };
};

