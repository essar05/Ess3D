#pragma once
#include <map>
#include "2d/model/Texture2D.h"
#include "TextureAtlas.h"

namespace Ess3D {

  class TextureAtlas;

  class TextureCache {
    public:
      ~TextureCache();

      Texture2D getTexture(std::string texturePath);
      TextureAtlas* getAtlas(std::string texturePath, std::string metadataPath);

	  static TextureCache* getInstance();

    protected:
      TextureCache();

    private:
      std::map<std::string, Ess3D::Texture2D> _textures;
      std::map<std::string, Ess3D::TextureAtlas*> _atlases;

	  static TextureCache* _instance;

  };

}