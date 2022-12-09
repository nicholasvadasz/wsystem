#include "Cylinder.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

void Cylinder::updateParams(int param1, int param2) {
  m_vertexData = std::vector<float>();
  m_param1 = param1;
  m_param2 = param2;
  setVertexData();
}

void Cylinder::makeTileSide(glm::vec3 topLeft, glm::vec3 topRight,
                            glm::vec3 bottomLeft, glm::vec3 bottomRight) {
  // Task 5: Implement the makeTile() function for a Sphere
  // Note: this function is very similar to the makeTile() function for Cube,
  //       but the normals are calculated in a different way!
  glm::vec3 topLeftNormal = glm::normalize(glm::vec3(topLeft.x, 0, topLeft.z));
  glm::vec3 topRightNormal =
      glm::normalize(glm::vec3(topRight.x, 0, topRight.z));
  glm::vec3 bottomLeftNormal =
      glm::normalize(glm::vec3(bottomLeft.x, 0, bottomLeft.z));
  glm::vec3 bottomRightNormal =
      glm::normalize(glm::vec3(bottomRight.x, 0, bottomRight.z));
  insertVec3(m_vertexData, topLeft);
  insertVec3(m_vertexData, topLeftNormal);
  insertVec3(m_vertexData, bottomLeft);
  insertVec3(m_vertexData, bottomLeftNormal);
  insertVec3(m_vertexData, bottomRight);
  insertVec3(m_vertexData, bottomRightNormal);

  insertVec3(m_vertexData, bottomRight);
  insertVec3(m_vertexData, bottomRightNormal);
  insertVec3(m_vertexData, topRight);
  insertVec3(m_vertexData, topRightNormal);
  insertVec3(m_vertexData, topLeft);
  insertVec3(m_vertexData, topLeftNormal);
}

void Cylinder::makeTileTopOrBot(glm::vec3 topLeft, glm::vec3 topRight,
                                glm::vec3 bottomLeft, glm::vec3 bottomRight,
                                glm::vec3 normal) {
  if (normal.y == 1) {
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, normal);

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, normal);
  } else {
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, normal);

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, normal);
  }
}

void Cylinder::makeWedge(float currentTheta, float nextTheta) {
  for (int i = 0; i < m_param1; i++) {
    float currentY = -0.5 + (i * 1.0 / m_param1);
    float nextY = -0.5 + ((i + 1) * 1.0 / m_param1);
    glm::vec3 topLeft = glm::vec3(m_radius * cos(currentTheta), currentY,
                                  m_radius * sin(currentTheta));
    glm::vec3 topRight = glm::vec3(m_radius * cos(nextTheta), currentY,
                                   m_radius * sin(nextTheta));
    glm::vec3 bottomLeft = glm::vec3(m_radius * cos(currentTheta), nextY,
                                     m_radius * sin(currentTheta));
    glm::vec3 bottomRight =
        glm::vec3(m_radius * cos(nextTheta), nextY, m_radius * sin(nextTheta));
    makeTileSide(topLeft, topRight, bottomLeft, bottomRight);
  }
}

void Cylinder::setVertexData() {
  float delta = glm::radians(360.f / m_param2);
  for (int i = 0; i < m_param2; i++) {
    float currentTheta = i * delta;
    float nextTheta = (i + 1) * delta;
    makeWedge(currentTheta, nextTheta);
  }
  glm::vec3 topCenter = glm::vec3(0, 0.5, 0);
  glm::vec3 bottomCenter = glm::vec3(0, -0.5, 0);
  glm::vec3 topNormal = glm::vec3(0, 1, 0);
  glm::vec3 bottomNormal = glm::vec3(0, -1, 0);
  for (int i = 0; i < m_param2; i++) {
    float delta = glm::radians(360.f / m_param2);
    float currentTheta = i * delta;
    float nextTheta = (i + 1) * delta;
    for (int j = 0; j < m_param1; j++) {
      float topLeftX =
          m_radius * cos(currentTheta) * (1 - (j * 1.0 / m_param1));
      float topLeftZ =
          m_radius * sin(currentTheta) * (1 - (j * 1.0 / m_param1));
      float topRightX = m_radius * cos(nextTheta) * (1 - (j * 1.0 / m_param1));
      float topRightZ = m_radius * sin(nextTheta) * (1 - (j * 1.0 / m_param1));
      float bottomLeftX =
          m_radius * cos(currentTheta) * (1 - ((j + 1) * 1.0 / m_param1));
      float bottomLeftZ =
          m_radius * sin(currentTheta) * (1 - ((j + 1) * 1.0 / m_param1));
      float bottomRightX =
          m_radius * cos(nextTheta) * (1 - ((j + 1) * 1.0 / m_param1));
      float bottomRightZ =
          m_radius * sin(nextTheta) * (1 - ((j + 1) * 1.0 / m_param1));
      glm::vec3 upTopLeft = glm::vec3(topLeftX, 0.5, topLeftZ);
      glm::vec3 upTopRight = glm::vec3(topRightX, 0.5, topRightZ);
      glm::vec3 upBottomLeft = glm::vec3(bottomLeftX, 0.5, bottomLeftZ);
      glm::vec3 upBottomRight = glm::vec3(bottomRightX, 0.5, bottomRightZ);
      glm::vec3 downTopLeft = glm::vec3(topLeftX, -0.5, topLeftZ);
      glm::vec3 downTopRight = glm::vec3(topRightX, -0.5, topRightZ);
      glm::vec3 downBottomLeft = glm::vec3(bottomLeftX, -0.5, bottomLeftZ);
      glm::vec3 downBottomRight = glm::vec3(bottomRightX, -0.5, bottomRightZ);
      makeTileTopOrBot(upTopLeft, upTopRight, upBottomLeft, upBottomRight,
                       topNormal);
      makeTileTopOrBot(downTopLeft, downTopRight, downBottomLeft,
                       downBottomRight, bottomNormal);
    }
  }
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build
// your shape!
void Cylinder::insertVec3(std::vector<float> &data, glm::vec3 v) {
  data.push_back(v.x);
  data.push_back(v.y);
  data.push_back(v.z);
}
