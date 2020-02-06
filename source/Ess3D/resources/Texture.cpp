#include "Texture.h"

namespace Ess3D {

  Texture::Texture() : _width(0), _height(0), _id(0), _mode(0), _type(ESS_TEX_TYPE_NONE) {
  }

  Texture::~Texture() {}

  GLuint Texture::getId() const {
    return _id;
  }

  TextureType Texture::getType() const {
    return _type;
  }

  int Texture::getHeight() const {
    return _height;
  }

  int Texture::getWidth() const {
    return _width;
  }

  int Texture::getMode() const {
    return _mode;
  }

  void Texture::setId(GLuint id) {
    _id = id;
  }

  void Texture::setType(TextureType type) {
    _type = type;
  }

  void Texture::setHeight(int height) {
    _height = height;
  }

  void Texture::setWidth(int width) {
    _width = width;
  }

  void Texture::setMode(int mode) {
    _mode = mode;
  }

}