#include "Cone.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>

void Cone::updateParams(int param1, int param2) {
  m_vertexData = std::vector<float>();
  m_param1 = param1;
  m_param2 = param2;
  setVertexData();
}

void Cone::makeTileSide(glm::vec3 topLeft, glm::vec3 topRight,
                        glm::vec3 bottomLeft, glm::vec3 bottomRight,
                        bool isTop) {
  glm::vec3 topLeftNormal = glm::normalize(glm::vec3(topLeft.x, 0, topLeft.z));
  glm::vec3 topRightNormal =
      glm::normalize(glm::vec3(topRight.x, 0, topRight.z));
  glm::vec3 tipNormal = glm::normalize(topLeftNormal + topRightNormal);
  tipNormal.y = .5;
  topLeftNormal.y = .5;
  topRightNormal.y = .5;
  if (!isTop) {
    glm::vec3 bottomLeftNormal =
        glm::normalize(glm::vec3(bottomLeft.x, 0, bottomLeft.z));
    bottomLeftNormal.y = .5;
    glm::vec3 bottomRightNormal =
        glm::normalize(glm::vec3(bottomRight.x, 0, bottomRight.z));
    bottomRightNormal.y = .5;
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
  } else {
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, topLeftNormal);
    insertVec3(m_vertexData, glm::vec3(0, .5, 0));
    insertVec3(m_vertexData, tipNormal);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, topRightNormal);
  }
};

void Cone::makeTileBot(glm::vec3 topLeft, glm::vec3 topRight,
                       glm::vec3 bottomLeft, glm::vec3 bottomRight) {
  glm::vec3 normal = glm::vec3(0, -1, 0);
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
};

void Cone::setVertexData() {
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
      glm::vec3 downTopLeft = glm::vec3(topLeftX, -0.5, topLeftZ);
      glm::vec3 downTopRight = glm::vec3(topRightX, -0.5, topRightZ);
      glm::vec3 downBottomLeft = glm::vec3(bottomLeftX, -0.5, bottomLeftZ);
      glm::vec3 downBottomRight = glm::vec3(bottomRightX, -0.5, bottomRightZ);
      makeTileBot(downTopLeft, downTopRight, downBottomLeft, downBottomRight);
      float currentY = -0.5 + (j * 1.0 / m_param1);
      float nextY = -0.5 + ((j + 1) * 1.0 / m_param1);
      glm::vec3 currentTopLeft = glm::vec3(topLeftX, currentY, topLeftZ);
      glm::vec3 currentTopRight = glm::vec3(topRightX, currentY, topRightZ);
      glm::vec3 currentBottomLeft = glm::vec3(bottomLeftX, nextY, bottomLeftZ);
      glm::vec3 currentBottomRight =
          glm::vec3(bottomRightX, nextY, bottomRightZ);
      makeTileSide(currentTopLeft, currentTopRight, currentBottomLeft,
                   currentBottomRight, j == m_param1 - 1);
    }
  }
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build
// your shape!
void Cone::insertVec3(std::vector<float> &data, glm::vec3 v) {
  data.push_back(v.x);
  data.push_back(v.y);
  data.push_back(v.z);
}
