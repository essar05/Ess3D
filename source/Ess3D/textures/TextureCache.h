#pragma once

#include <map>
#include "Texture.h"
#include "TextureAtlas.h"

namespace Ess3D {

  class TextureAtlas;

  class TextureCache {
    public:
      ~TextureCache();

      Texture* getTexture(std::string texturePath);
      TextureAtlas* getAtlas(std::string texturePath, std::string metadataPath);

      static TextureCache* getInstance();

    protected:
      TextureCache();

    private:
      std::map<std::string, Ess3D::Texture*> _textures;
      std::map<std::string, Ess3D::TextureAtlas*> _atlases;

      Texture* loadTextureFromFile(std::string texturePath);
      Texture loadAtlasMetadataFromFile(TextureAtlas* atlas, std::string metadataPath);

      static TextureCache* _instance;

  };

}