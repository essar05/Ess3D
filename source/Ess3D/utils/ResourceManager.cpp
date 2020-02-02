#include "ResourceManager.h"

namespace Ess3D {

  Texture2D ResourceManager::getTexture(std::string texturePath) {
    return TextureCache::getInstance()->getTexture(texturePath);
  }

}