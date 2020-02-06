#pragma once

#include <GL/glew.h>

namespace Ess3D {

  enum TextureType {
    ESS_TEX_TYPE_NONE,
    ESS_TEX_TYPE_DIFFUSE,
    ESS_TEX_TYPE_SPECULAR,
    ESS_TEX_TYPE_NORMAL,
    ESS_TEX_TYPE_HEIGHT
  };

  class Texture {
    public:
      //methods
      Texture();
      ~Texture();

      GLuint getId() const;
      TextureType getType() const;
      int getHeight() const;
      int getWidth() const;
      int getMode() const;

      void setId(GLuint id);
      void setType(TextureType type);
      void setHeight(int height);
      void setWidth(int width);
      void setMode(int mode);

    private:
      GLuint _id;
      TextureType _type;

      int _height;
      int _width;

      int _mode;
  };

}