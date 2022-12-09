#include "Triangle.h"

// make a const of "base points", 4 vertices making a square base

void Triangle::updateParams(int param1, int param2) {
  m_vertexData = std::vector<float>();
  setVertexData();
  m_param1 = param1;
  m_param2 = param2;
}

void Triangle::makeTile(glm::vec3 topLeft, glm::vec3 topRight,
                        glm::vec3 bottomLeft, glm::vec3 bottomRight) {
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

void Triangle::makeTriangle(glm::vec3 bottomLeft, glm::vec3 bottomRight,
                            glm::vec3 top) {
  glm::vec3 CA1 = bottomRight - bottomLeft;
  glm::vec3 CB1 = top - bottomLeft;
  glm::vec3 normal1 = glm::normalize(glm::cross(CA1, CB1));
  // reverse normal
  normal1 = -normal1;
  insertVec3(m_vertexData, bottomRight);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, bottomLeft);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, top);
  insertVec3(m_vertexData, normal1);
}

void Triangle::makeColumn(std::vector<glm::vec3> basePoints, float height,
                          float splitPoint, bool pointyTop) {

  glm::vec3 growthDirection = glm::normalize(
      glm::cross(basePoints[1] - basePoints[0], basePoints[2] - basePoints[0]));
  if (growthDirection.y < 0) {
    growthDirection = -growthDirection;
  }
  std::vector<glm::vec3> topPoints = {
      basePoints[0] + growthDirection * splitPoint * height,
      basePoints[1] + growthDirection * splitPoint * height,
      basePoints[2] + growthDirection * splitPoint * height,
      basePoints[3] + growthDirection * splitPoint * height};
  makeTile(basePoints[0], basePoints[1], topPoints[0], topPoints[1]);
  makeTile(basePoints[1], basePoints[2], topPoints[1], topPoints[2]);
  makeTile(basePoints[2], basePoints[3], topPoints[2], topPoints[3]);
  makeTile(basePoints[3], basePoints[0], topPoints[3], topPoints[0]);
  if (!pointyTop) {
    makeTriangle(topPoints[0], topPoints[1], topPoints[2]);
    makeTriangle(topPoints[2], topPoints[3], topPoints[0]);
  } else {
    // middle point is average of all 4 points
    glm::vec3 tipPoint =
        (basePoints[0] + basePoints[1] + basePoints[2] + basePoints[3]) / 4.0f;
    // then add the total growth direction to it
    tipPoint += growthDirection * height;
    makeTriangle(topPoints[0], topPoints[1], tipPoint);
    makeTriangle(topPoints[1], topPoints[2], tipPoint);
    makeTriangle(topPoints[2], topPoints[3], tipPoint);
    makeTriangle(topPoints[3], topPoints[0], tipPoint);
  }
}

void Triangle::setVertexData() {
  std::vector<glm::vec3> basePoints = {
      // make them all have the same y value
      glm::vec3(-0.2, -1, -0.2),
      glm::vec3(0.2, -1.3, -0.2),
      glm::vec3(0.2, -1.3, 0.2),
      glm::vec3(-0.2, -1, 0.2),
  };
  std::vector<glm::vec3> base2Points = {
      // make them all have the same y value
      glm::vec3(-0.3, -1, -0.1),
      glm::vec3(-0.1, -1, -0.2),
      glm::vec3(-0.1, -1, 0.2),
      glm::vec3(-0.3, -1, 0.3),
  };
  makeColumn(basePoints, 2, .8, true);
  makeColumn(base2Points, 1.7, .9, true);
}
// make face growing down in the direction of that normal}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build
// your shape!
void Triangle::insertVec3(std::vector<float> &data, glm::vec3 v) {
  data.push_back(v.x);
  data.push_back(v.y);
  data.push_back(v.z);
}
