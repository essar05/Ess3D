#pragma once

#include <string>
#include <glm\glm.hpp>
#include <unordered_map>
#include "Texture.h"
#include "TextureAtlasSection.h"

namespace Ess3D {

  class TextureAtlas {
    public:
      TextureAtlas();
      ~TextureAtlas();

      glm::vec4 getUV(std::string sectionName);
      glm::vec2 getSize(std::string sectionName);

      Texture* getTexture() const;
      void setTexture(Texture* texture);

      void addSection(std::string name, int height, int width, int x, int y);

    private:
      Texture* _texture;
      std::unordered_map<std::string, TextureAtlasSection*> _sections;

  };

};