#pragma once

#include <Ess3D/definitions.h>
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include <Ess3D/resources/Texture.h>
#include <Ess3D/resources/TextureAtlasSection.h>

namespace Ess3D {

  class API TextureAtlas {
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