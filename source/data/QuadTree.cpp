#include <Ess3D/data/QuadTree.h>

#include <utility>

namespace Ess3D {

  /******************
   *    QUADTREE
   ******************/

  QuadTree::QuadTree( const glm::vec2& size, unsigned short maxDepth, unsigned short maxElementsPerNode )
    : _maxDepth(maxDepth), _maxElementsPerNode(maxElementsPerNode) {
    _rootNode = new QuadNode(BoundingBox(
      glm::vec2(-size.x / 2, size.y / 2),
      glm::vec2(size.x / 2, -size.y / 2)
    ));
  }

  void QuadTree::insert( int32_t elementId, const BoundingBox& elementBoundingBox ) {
    // If the tree is empty
    _rootNode->insert(elementId, elementBoundingBox, _maxDepth, _maxElementsPerNode);
  }

  /******************
   *    QUADNODE
   ******************/

  QuadNode::QuadNode( BoundingBox boundingBox ) : _nodeBoundingBox(std::move(boundingBox)) {}

  bool QuadNode::insert( int32_t elementId, const BoundingBox& elementBoundingBox, unsigned short height,
                         unsigned short maxElementsPerNode ) {
    if (!_nodeBoundingBox.intersects(elementBoundingBox)) {
      return false;
    }

    if (this->isLeaf()) {
      if (this->isLeaf() && ( height == 0 || _elements.size() < maxElementsPerNode - 1 )) {
        _elements.push_back(elementId);
        _elementBoundingBoxes.emplace_back(elementBoundingBox);

        return true;
      }

      if (height > 0 && _elements.size() == maxElementsPerNode) {
        this->split();
      }
    }

    for (unsigned short i = 0; i < 4; i++) {
      this->_children[i].insert(elementId, elementBoundingBox, height - 1, maxElementsPerNode);

      while (!_elements.empty()) {
        this->_children[i].insert(_elements.back(), _elementBoundingBoxes.back(), height - 1, maxElementsPerNode);
        _elements.pop_back();
        _elementBoundingBoxes.pop_back();
      }
    }

    return true;
  }

  void QuadNode::split() {
    this->_children = (QuadNode*) malloc(sizeof(QuadNode) * 4);

    float halfX = _nodeBoundingBox.topLeft.x + ( _nodeBoundingBox.bottomRight.x - _nodeBoundingBox.topLeft.x ) / 2;
    float halfY = _nodeBoundingBox.bottomRight.y + ( _nodeBoundingBox.topLeft.y - _nodeBoundingBox.bottomRight.y ) / 2;

    // NORTH WEST
    this->_children[0] = QuadNode(
      BoundingBox(
        glm::vec2(_nodeBoundingBox.topLeft.x, _nodeBoundingBox.topLeft.y),
        glm::vec2(halfX, halfY)
      )
    );

    // NORTH EAST
    this->_children[1] = QuadNode(
      BoundingBox(
        glm::vec2(halfX, _nodeBoundingBox.topLeft.y),
        glm::vec2(_nodeBoundingBox.bottomRight.x, halfY)
      )
    );

    // SOUTH EAST
    this->_children[2] = QuadNode(
      BoundingBox(
        glm::vec2(halfX, halfY),
        glm::vec2(_nodeBoundingBox.bottomRight.x, _nodeBoundingBox.bottomRight.y)
      )
    );

    // SOUTH WEST
    this->_children[2] = QuadNode(
      BoundingBox(
        glm::vec2(_nodeBoundingBox.topLeft.x, halfY),
        glm::vec2(halfX, _nodeBoundingBox.bottomRight.y)
      )
    );
  }

  bool QuadNode::isLeaf() {
    return this->_children == nullptr;
  }

  /*******************
   *    RECTANGLE
   *******************/

  BoundingBox::BoundingBox( const glm::vec2& topLeft, const glm::vec2& bottomRight ) : topLeft(topLeft),
                                                                                       bottomRight(bottomRight) {}

  BoundingBox::BoundingBox( const BoundingBox& boundingBox ) : BoundingBox(boundingBox.topLeft,
                                                                           boundingBox.bottomRight) {}

  bool BoundingBox::intersects( const BoundingBox& boundingBox ) const {
    if (this->topLeft.x >= boundingBox.bottomRight.x || boundingBox.topLeft.x >= this->bottomRight.x) {
      return false;
    }

    if (this->topLeft.y <= boundingBox.bottomRight.y || boundingBox.topLeft.y <= this->bottomRight.y) {
      return false;
    }

    return true;
  }


}