#include "TextureCache.h"
#include <GL/glew.h>
#include <rapidjson.h>
#include <SDL_image.h>
#include <fstream>
#include <document.h>
#include "errors/RuntimeException.cpp"

namespace Ess3D {

  TextureCache::TextureCache() {}

  TextureCache::~TextureCache() {
    auto itTex = _textures.begin();
    while (itTex != _textures.end()) {
      delete itTex->second;
      itTex++;
    }

    auto itAtlas = _atlases.begin();
    while (itAtlas != _atlases.end()) {
      delete itAtlas->second;
      itAtlas++;
    }
  }

  Texture* TextureCache::getTexture(std::string texturePath) {
    auto it = _textures.find(texturePath);

    if (it == _textures.end()) {
      Texture* texture = this->loadTextureFromFile(texturePath);

      _textures.insert(make_pair(texturePath, texture));

      return texture;
    }

    return it->second;
  }

  TextureAtlas* TextureCache::getAtlas(std::string texturePath, std::string metadataPath) {
    std::string key = texturePath + "_" + metadataPath;
    auto it = _atlases.find(key);

    if (it == _atlases.end()) {
      TextureAtlas* atlas = new TextureAtlas();

      atlas->setTexture(this->loadTextureFromFile(texturePath));

      this->loadAtlasMetadataFromFile(atlas, metadataPath);

      _atlases.insert(std::make_pair(key, atlas));

      return atlas;
    }

    return it->second;
  }

  Texture* TextureCache::loadTextureFromFile(std::string texturePath) {
    Texture* texture = new Texture();

    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
      throw ERuntimeException("Error loading image: " + texturePath);
    }

    if (surface->format->BytesPerPixel == 3) { // RGB 24bit
      texture->setMode(GL_RGB);
    } else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
      texture->setMode(GL_RGBA);
    } else {
      SDL_FreeSurface(surface);
      throw ERuntimeException("Unknown image format: " + texturePath);
    }

    texture->setWidth(surface->w);
    texture->setHeight(surface->h);

    GLuint generatedId;

    glGenTextures(1, &generatedId);

    texture->setId(generatedId);

    glBindTexture(GL_TEXTURE_2D, texture->getId());
    glTexImage2D(GL_TEXTURE_2D, 0, texture->getMode(), texture->getWidth(), texture->getHeight(), 0, texture->getMode(),
                 GL_UNSIGNED_BYTE, surface->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface);

    return texture;
  }

  Texture TextureCache::loadAtlasMetadataFromFile(TextureAtlas* atlas, std::string metadataPath) {
    std::ifstream fileStream(metadataPath);
    std::string jsonData;

    if (!fileStream.is_open()) {
      throw ERuntimeException("Failed to open " + metadataPath);
    }

    fileStream.seekg(0, std::ios::end);
    jsonData.reserve((unsigned int) fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);

    jsonData.assign(( std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    rapidjson::Document document;
    document.Parse(jsonData.c_str());

    if (!document.IsArray()) {
      throw ERuntimeException("Texture atlas metadata file invalid " + metadataPath);
    }

    for (rapidjson::SizeType i = 0; i < document.Size(); i++) {
      atlas->addSection(
          document[i]["name"].GetString(),
          document[i]["width"].GetInt(),
          document[i]["height"].GetInt(),
          document[i]["x"].GetInt(),
          document[i]["y"].GetInt()
      );
    }
  }

  TextureCache* TextureCache::_instance = nullptr;

  TextureCache* TextureCache::getInstance() {
    if (_instance == nullptr) {
      _instance = new TextureCache();
    }

    return _instance;
  }

}