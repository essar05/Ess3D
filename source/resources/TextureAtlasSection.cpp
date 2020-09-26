#include <Ess3D/resources/TextureAtlasSection.h>

namespace Ess3D {

  const std::string &TextureAtlasSection::getName() const {
    return _name;
  }

  int TextureAtlasSection::getX() const {
    return _x;
  }

  int TextureAtlasSection::getY() const {
    return _y;
  }

  int TextureAtlasSection::getWidth() const {
    return _width;
  }

  int TextureAtlasSection::getHeight() const {
    return _height;
  }

  const glm::vec4 &TextureAtlasSection::getUV() const {
    return _uv;
  }

  void TextureAtlasSection::setName(const std::string &name) {
    _name = name;
  }

  void TextureAtlasSection::setX(int x) {
    _x = x;
  }

  void TextureAtlasSection::setY(int y) {
    _y = y;
  }

  void TextureAtlasSection::setWidth(int width) {
    _width = width;
  }

  void TextureAtlasSection::setHeight(int height) {
    _height = height;
  }

  void TextureAtlasSection::generateUV(int atlasWidth, int atlasHeight) {
    _uv.x = (float) this->_x / (float) atlasWidth;
    _uv.y =
      1.0f - (float) (this->_y + this->_height) / (float) atlasHeight;
    _uv.z = (float) this->_width / (float) atlasWidth;
    _uv.w = (float) this->_height / (float) atlasHeight;
  }

}