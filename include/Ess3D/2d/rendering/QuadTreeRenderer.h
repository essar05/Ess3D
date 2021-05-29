#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/gl/ColorRGBA8.h>

namespace Ess3D {

  class QuadTree;
  class QuadNode;
  struct BoundingBox;
  class Renderer2D;

  class API QuadTreeRenderer {
    public:

      static void renderTree( const Renderer2D& renderer2D, const QuadTree& quadTree );
      static void renderNode( const Renderer2D& renderer2D, const QuadNode& quadNode );

      static void renderBoundingBox( const Renderer2D& renderer2D, const BoundingBox& boundingBox, const ColorRGBA8& color );
  };

}
