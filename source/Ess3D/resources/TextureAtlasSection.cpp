#include "TextureAtlasSection.h"

const std::string& Ess3D::TextureAtlasSection::getName() const {
  return _name;
}

int Ess3D::TextureAtlasSection::getX() const {
  return _x;
}

int Ess3D::TextureAtlasSection::getY() const {
  return _y;
}

int Ess3D::TextureAtlasSection::getWidth() const {
  return _width;
}

int Ess3D::TextureAtlasSection::getHeight() const {
  return _height;
}

const glm::vec4& Ess3D::TextureAtlasSection::getUV() const {
  return _uv;
}

void Ess3D::TextureAtlasSection::setName(const std::string& name) {
  _name = name;
}

void Ess3D::TextureAtlasSection::setX(int x) {
  _x = x;
}

void Ess3D::TextureAtlasSection::setY(int y) {
  _y = y;
}

void Ess3D::TextureAtlasSection::setWidth(int width) {
  _width = width;
}

void Ess3D::TextureAtlasSection::setHeight(int height) {
  _height = height;
}

void Ess3D::TextureAtlasSection::generateUV(int atlasWidth, int atlasHeight) {
  _uv.x = (float) this->_x / (float) atlasWidth;
  _uv.y =
      1.0f - (float) ( this->_y + this->_height ) / (float) atlasHeight;
  _uv.z = (float) this->_width / (float) atlasWidth;
  _uv.w = (float) this->_height / (float) atlasHeight;
}
