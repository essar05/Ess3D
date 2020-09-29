#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <Ess3D/2d/rendering/QuadTreeRenderer.h>

namespace Ess3D {

  class QuadNode;
  struct BoundingBox;

  class QuadTree {
      friend QuadTreeRenderer;

    public:
      explicit QuadTree( const glm::vec2& size, unsigned short maxDepth = 7, unsigned short maxElementsPerNode = 5 );

      void insert( int32_t elementId, const BoundingBox& elementBoundingBox );

    protected:
      QuadNode* _rootNode = nullptr;

      unsigned short _maxDepth;
      unsigned short _maxElementsPerNode;

  };

  struct BoundingBox {
    BoundingBox( const BoundingBox& boundingBox );
    BoundingBox( const glm::vec2& topLeft, const glm::vec2& bottomRight );

    bool intersects( const BoundingBox& boundingBox ) const;

    glm::vec2 topLeft;
    glm::vec2 bottomRight;
  };

  class QuadNode {
      friend QuadTree;
      friend QuadTreeRenderer;

    public:
      explicit QuadNode( BoundingBox boundingBox );

    protected:
      bool insert( int32_t elementId, const BoundingBox& elementBoundingBox, unsigned short height,
                   unsigned short maxElementsPerNode );

      void split();

      bool isLeaf();

      QuadNode* _children = nullptr;

      std::vector<int32_t> _elements;
      std::vector<BoundingBox> _elementBoundingBoxes;

      BoundingBox _nodeBoundingBox;
  };

}