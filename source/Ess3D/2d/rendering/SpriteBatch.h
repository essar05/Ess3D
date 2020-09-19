#pragma once

#include "definitions.h"
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "2d/models/Vertex2D.h"

namespace Ess3D {

  class Sprite {
    public:
      Sprite();

      glm::vec2 position;
      glm::vec2 size;
      glm::vec4 uv;
      GLuint textureId = 0;
      ColorRGBA8 color;
      float zDepth = 1.0f;
      float angle = 0.0f;
  };

  class API RenderBatch {
    public:
      RenderBatch(GLuint offset, GLuint numVertices, GLuint textureId) {
        this->offset = offset;
        this->numVertices = numVertices;
        this->textureId = textureId;
      }

      GLuint offset;
      GLuint numVertices;
      GLuint textureId;
  };

  class API SpriteBatch {
    public:
      SpriteBatch();
      ~SpriteBatch();

      void init();

      void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
      void end();

      void addToQueue(const Sprite& sprite);

      void render();

    private:
      void createVertexArray();
      void sortGlyphs();
      void createRenderBatches();

      static bool compareBackToFront(Glyph *a, Glyph *b);
      static bool compareFrontToBack(Glyph *a, Glyph *b);
      static bool compareTexture(Glyph *a, Glyph *b);

      GLuint _vbo;
      GLuint _vao;

      GlyphSortType _sortType;

      std::vector<Glyph> _glyphs; //actual glyphs
      std::vector<Glyph *> _glyphPointers; //for sorting
      std::vector<RenderBatch> _renderBatches;


  };

}