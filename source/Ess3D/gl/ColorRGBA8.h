#pragma once

namespace Ess3D {
  struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(255) {}

    ColorRGBA8(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {}

    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
  };
}