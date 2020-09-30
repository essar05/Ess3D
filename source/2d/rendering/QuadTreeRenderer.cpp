#include <Ess3D/2d/rendering/QuadTreeRenderer.h>
#include <Ess3D/data/QuadTree.h>

namespace Ess3D {

  void QuadTreeRenderer::renderTree( const Renderer2D& renderer2D, const QuadTree& quadTree ) {
    renderNode(renderer2D, *quadTree._rootNode);
  }

  void QuadTreeRenderer::renderNode( const Renderer2D& renderer2D, const QuadNode& quadNode ) {
    renderBoundingBox(renderer2D, quadNode._nodeBoundingBox, ColorRGBA8(255, 0, 0, 255));

    if (!quadNode.isLeaf()) {
      for (unsigned short i = 0; i < 4; i++) {

        renderNode(renderer2D, *quadNode._children[i]);
      }
    }

  }

  void QuadTreeRenderer::renderBoundingBox( const Renderer2D& renderer2D, const BoundingBox& boundingBox,
                                            const ColorRGBA8& color ) {
    int vertexCount = 4;

    GLfloat r = 1.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    GLfloat a = 1.0f;

    GLfloat vert[] = {
      boundingBox.bottomRight.x, boundingBox.bottomRight.y, r, g, b, a,
      boundingBox.topLeft.x, boundingBox.bottomRight.y, r, g, b, a,
      boundingBox.topLeft.x, boundingBox.topLeft.y, r, g, b, a,
      boundingBox.bottomRight.x, boundingBox.topLeft.y, r, g, b, a,
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) ( 2 * sizeof(GLfloat)));

    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
  }

}