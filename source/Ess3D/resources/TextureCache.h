#pragma once

#include <map>
#include "Texture.h"
#include "TextureAtlas.h"

namespace Ess3D {

  class TextureAtlas;

  class TextureCache {
    public:
      ~TextureCache();

      Texture* getTexture(const std::string& texturePath);
      bool isTextureCached(const std::string& texturePath);

      TextureAtlas* getAtlas(const std::string& texturePath, const std::string& metadataPath);

      static TextureCache* getInstance();

    protected:
      TextureCache();

    private:
      std::map<std::string, Texture*> _textures;
      std::map<std::string, TextureAtlas*> _atlases;

      Texture* loadTextureFromFile(const std::string& texturePath);
      Texture loadAtlasMetadataFromFile(TextureAtlas* atlas, const std::string& metadataPath);

      static TextureCache* _instance;

  };

}