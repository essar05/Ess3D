#include <Ess3D/resources/TextureAtlas.h>

namespace Ess3D {

  TextureAtlas::TextureAtlas() {}

  TextureAtlas::~TextureAtlas() {
    auto it = _sections.begin();
    while (it != _sections.end()) {
      delete it->second;
      it++;
    }
  }

  glm::vec4 TextureAtlas::getUV(std::string sectionName) {
    auto it = _sections.find(sectionName);
    if (it != _sections.end()) {
      return it->second->getUV();
    }

    return glm::vec4(0.0f);
  }

  glm::vec2 TextureAtlas::getSize(std::string sectionName) {
    auto it = _sections.find(sectionName);
    if (it != _sections.end()) {
      return glm::vec2(it->second->getWidth(), it->second->getHeight());
    }

    return glm::vec2(0.0f);
  }

  void TextureAtlas::addSection(std::string name, int height, int width, int x, int y) {
    TextureAtlasSection* section = new TextureAtlasSection();

    section->setName(name);
    section->setHeight(height);
    section->setWidth(width);
    section->setX(x);
    section->setY(y);
    section->generateUV(this->_texture->getWidth(), this->_texture->getHeight());

    _sections.insert(std::pair<std::string, TextureAtlasSection*>(name, section));
  }

  Texture* TextureAtlas::getTexture() const {
    return _texture;
  }

  void TextureAtlas::setTexture(Texture* texture) {
    _texture = texture;
  }

}