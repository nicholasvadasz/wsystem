#include "Cube.h"

void Cube::updateParams(int param1) {
  m_vertexData = std::vector<float>();
  m_param1 = param1;
  setVertexData();
}

void Cube::makeTile(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                    glm::vec3 bottomRight) {
  // Task 2: create a tile (i.e. 2 triangles) based on 4 given points.
  //   normal for each triangle is CB x CA
  glm::vec3 CA1 = bottomRight - bottomLeft;
  glm::vec3 CB1 = topLeft - bottomLeft;
  glm::vec3 normal1 = glm::normalize(glm::cross(CA1, CB1));
  insertVec3(m_vertexData, bottomLeft);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, bottomRight);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, topLeft);
  insertVec3(m_vertexData, normal1);
  glm::vec3 CA2 = topRight - topLeft;
  glm::vec3 CB2 = bottomRight - topLeft;
  glm::vec3 normal2 = glm::normalize(glm::cross(CB2, CA2));
  insertVec3(m_vertexData, topLeft);
  insertVec3(m_vertexData, normal2);
  insertVec3(m_vertexData, bottomRight);
  insertVec3(m_vertexData, normal2);
  insertVec3(m_vertexData, topRight);
  insertVec3(m_vertexData, normal2);
}

void Cube::makeFace(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                    glm::vec3 bottomRight) {
  // Task 3: create a single side of the cube out of the 4
  //         given points and makeTile()
  // Note: think about how param 1 affects the number of triangles on
  //       the face of the cube
  for (int i = 0; i < m_param1; i++) {
    for (int j = 0; j < m_param1; j++) {
      glm::vec3 newTopLeft =
          glm::vec3(topLeft.x + (topRight.x - topLeft.x) / m_param1 * i +
                        j * (bottomLeft.x - topLeft.x) / m_param1,
                    topLeft.y + (topRight.y - topLeft.y) / m_param1 * i +
                        j * (bottomLeft.y - topLeft.y) / m_param1,
                    topLeft.z + (topRight.z - topLeft.z) / m_param1 * i +
                        j * (bottomLeft.z - topLeft.z) / m_param1);
      glm::vec3 newTopRight =
          glm::vec3(newTopLeft.x + (topRight.x - topLeft.x) / m_param1,
                    newTopLeft.y + (topRight.y - topLeft.y) / m_param1,
                    newTopLeft.z + (topRight.z - topLeft.z) / m_param1);
      glm::vec3 newBottomLeft =
          glm::vec3(newTopLeft.x + (bottomLeft.x - topLeft.x) / m_param1,
                    newTopLeft.y + (bottomLeft.y - topLeft.y) / m_param1,
                    newTopLeft.z + (bottomLeft.z - topLeft.z) / m_param1);
      glm::vec3 newBottomRight =
          glm::vec3(newBottomLeft.x + (topRight.x - topLeft.x) / m_param1,
                    newBottomLeft.y + (topRight.y - topLeft.y) / m_param1,
                    newBottomLeft.z + (topRight.z - topLeft.z) / m_param1);
      makeTile(newTopLeft, newTopRight, newBottomLeft, newBottomRight);
    }
  }
}

void Cube::setVertexData() {
  // Uncomment these lines for Task 2, then comment them out for Task 3:

  //   makeTile(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
  //            glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f));

  // Uncomment these lines for Task 3:

  makeFace(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
           glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f));

  // Task 4: Use the makeFace() function to make all 6 sides of the cube

  makeFace(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
           glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f));

  makeFace(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f),
           glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f));

  makeFace(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
           glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f));

  makeFace(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
           glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));

  makeFace(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f),
           glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f));
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build
// your shape!
void Cube::insertVec3(std::vector<float> &data, glm::vec3 v) {
  data.push_back(v.x);
  data.push_back(v.y);
  data.push_back(v.z);
}
