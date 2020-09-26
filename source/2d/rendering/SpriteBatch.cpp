#include <Ess3D/2d/rendering/SpriteBatch.h>
#include <algorithm>

namespace Ess3D {

  Sprite::Sprite() = default;

  SpriteBatch::SpriteBatch() : _vbo(0), _vao(0), _sortType(GlyphSortType::TEXTURE) {}

  SpriteBatch::~SpriteBatch() = default;

  void SpriteBatch::init() {
    createVertexArray();
  }

  void SpriteBatch::begin(GlyphSortType sortType) {
    _sortType = sortType;
    _renderBatches.clear();
    _glyphs.clear();
  }

  void SpriteBatch::end() {
    _glyphPointers.resize(_glyphs.size());
    for(unsigned int i = 0; i < _glyphs.size(); i++) {
      _glyphPointers[i] = &_glyphs[i];
    }

    sortGlyphs();
    createRenderBatches();
  }

  void SpriteBatch::addToQueue(const Sprite& sprite) {
    _glyphs.emplace_back(sprite.position, sprite.size, sprite.uv, sprite.textureId, sprite.color, sprite.zDepth, sprite.angle);
  }

  void SpriteBatch::render() {
    glBindVertexArray(_vao);
    glActiveTexture(GL_TEXTURE0);

    for(auto & renderBatch : _renderBatches) {
      glBindTexture(GL_TEXTURE_2D, renderBatch.textureId);

      glDrawArrays(GL_TRIANGLES, renderBatch.offset, renderBatch.numVertices);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
  
    glBindVertexArray(0);
  }

  void SpriteBatch::createVertexArray() {
    if(_vao == 0) {
      glGenVertexArrays(1, &_vao);
    }
    glBindVertexArray(_vao);

    if(_vbo == 0) {
      glGenBuffers(1, &_vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    //enabling the attribute array. not sure if need to do this since we do that in Shader::use ??
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //position attribute pointer.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*) offsetof(Vertex2D, position));
    //color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D), (void*) offsetof(Vertex2D, color));
    //texture uv coordinates pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*) offsetof(Vertex2D, uv));

    glBindVertexArray(0);
  }

  void SpriteBatch::createRenderBatches() {
    std::vector<Vertex2D> vertices;
    vertices.resize(_glyphPointers.size() * 6);

    if(_glyphPointers.empty()) {
      return;
    }

    int k = 0;
    int offset = 0;

    //setup the first batch just to avoid more ifs inside a for. isntead we'll start the for from the 1 index.
    _renderBatches.emplace_back(offset, 6, _glyphPointers[0]->textureId);
    
    //add the vertices of the first glyph in our vector
    vertices[k++] = _glyphPointers[0]->topLeftVertex;
    vertices[k++] = _glyphPointers[0]->bottomLeftVertex;
    vertices[k++] = _glyphPointers[0]->bottomRightVertex;
    vertices[k++] = _glyphPointers[0]->bottomRightVertex;
    vertices[k++] = _glyphPointers[0]->topRightVertex;
    vertices[k++] = _glyphPointers[0]->topLeftVertex;
    offset += 6;

    for(unsigned int i = 1; i < _glyphPointers.size(); i++) {
      //only create a new batch if the texture of the glyph is different.
      if(_glyphPointers[i]->textureId != _glyphPointers[i - 1]->textureId) {
        _renderBatches.emplace_back(offset, 6, _glyphPointers[i]->textureId);
      } else {
        _renderBatches.back().numVertices += 6;
      }
      
      //add the vertices of glyph i in our vector
      vertices[k++] = _glyphPointers[i]->topLeftVertex;
      vertices[k++] = _glyphPointers[i]->bottomLeftVertex;
      vertices[k++] = _glyphPointers[i]->bottomRightVertex;
      vertices[k++] = _glyphPointers[i]->bottomRightVertex;
      vertices[k++] = _glyphPointers[i]->topRightVertex;
      vertices[k++] = _glyphPointers[i]->topLeftVertex;
      offset += 6;
    }


    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    //clear the buffer. it's faster than just uploading directly.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), nullptr, GL_DYNAMIC_DRAW);
    //upload the vertices data to the vertex buffer object.
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex2D), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void SpriteBatch::sortGlyphs() {
    switch(_sortType) {
      case GlyphSortType::BACK_TO_FRONT:
        std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
        break;
      case GlyphSortType::FRONT_TO_BACK:
        std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
        break;
      case GlyphSortType::TEXTURE:
        std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
        break;
    }
  }

  bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
    return (a->zDepth < b->zDepth);
  }

  bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
    return (a->zDepth > b->zDepth);
  }

  bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
    return (a->textureId < b->textureId);
  }
}