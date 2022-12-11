#include "Triangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

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
  normal1 = -normal1;
  insertVec3(m_vertexData, bottomRight);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, bottomLeft);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, top);
  insertVec3(m_vertexData, normal1);
}

void Triangle::makeColumn(std::vector<glm::vec3> basePoints, float height,
                          float splitPoint, float growOutAmount,
                          bool pointyTop) {
  glm::vec3 growthDirection = glm::vec3(0.0f);
  for (int i = 0; i < basePoints.size(); i++) {
    growthDirection += glm::normalize(
        glm::cross(basePoints[(i + 1) % basePoints.size()] - basePoints[i],
                   basePoints[(i + 2) % basePoints.size()] - basePoints[i]));
  }
  growthDirection = glm::normalize(growthDirection);
  if (growthDirection.y < 0) {
    growthDirection = -growthDirection;
  }
  std::vector<glm::vec3> topPoints = std::vector<glm::vec3>();
  for (int i = 0; i < basePoints.size(); i++) {
    topPoints.push_back(basePoints[i] + growthDirection * height * splitPoint);
  }
  glm::vec3 middleTopPoint = glm::vec3(0.0f);
  for (int i = 0; i < topPoints.size(); i++) {
    middleTopPoint += topPoints[i];
  }
  middleTopPoint /= topPoints.size();
  for (int i = 0; i < topPoints.size(); i++) {
    topPoints[i] += (topPoints[i] - middleTopPoint) * growOutAmount;
  }
  for (int i = 0; i < basePoints.size(); i++) {
    makeTile(basePoints[i], basePoints[(i + 1) % basePoints.size()],
             topPoints[i], topPoints[(i + 1) % topPoints.size()]);
  }
  if (!pointyTop) {
    for (int i = 0; i < topPoints.size(); i++) {
      makeTriangle(topPoints[i], topPoints[(i + 1) % topPoints.size()],
                   middleTopPoint);
    }
  } else {
    // middle point is average of all 4 points
    glm::vec3 tipPoint = glm::vec3(0.0f);
    for (int i = 0; i < topPoints.size(); i++) {
      tipPoint += topPoints[i];
    }
    tipPoint /= topPoints.size();
    tipPoint += growthDirection * height * (1 - splitPoint);
    for (int i = 0; i < topPoints.size(); i++) {
      makeTriangle(topPoints[i], topPoints[(i + 1) % topPoints.size()],
                   tipPoint);
    }
  }
}

void Triangle::setVertexData() {
  glm::vec3 baseCenter = glm::vec3(0.0f, 0.0f, 0.0f);
  std::vector<std::vector<glm::vec3>> basePoints =
      std::vector<std::vector<glm::vec3>>();
  for (int i = 0; i < 30; i++) {
    std::vector<glm::vec3> base = std::vector<glm::vec3>();
    for (int j = 0; j < 4; j++) {
      base.push_back(baseCenter + glm::vec3(0.2f * cos(j * M_PI / 2), 0.0f,
                                            0.2f * sin(j * M_PI / 2)));
    }
    basePoints.push_back(base);
  }
  for (int i = 0; i < basePoints.size(); i++) {
    float xAngle = (float)(rand() % 100) * M_PI / 180;
    if (rand() % 2 == 0) {
      xAngle = -xAngle;
    }
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), xAngle, glm::vec3(1.0f, -1.0f, 0.0f));
    float zAngle = (float)(rand() % 100) * M_PI / 180;
    if (rand() % 2 == 0) {
      zAngle = -zAngle;
    }
    rotationMatrix =
        glm::rotate(rotationMatrix, zAngle, glm::vec3(0.0f, -1.0f, 1.0f));
    for (int j = 0; j < basePoints[i].size(); j++) {
      basePoints[i][j] =
          glm::vec3(rotationMatrix * glm::vec4(basePoints[i][j], 1.0f));
    }
  }
  for (int i = 0; i < basePoints.size(); i++) {
    for (int j = 0; j < basePoints[i].size(); j++) {
      basePoints[i][j] -= glm::vec3(0.0f, .5f, 0.0f);
    }
  }
  for (int i = 0; i < basePoints.size(); i++) {
    float height = (float)(rand() % 100) / 100 + 0.5;
    float splitPoint = (float)(rand() % 60) / 100 + 0.2;
    float growOutAmount = (float)(rand() % 20) / 100 + 0.1;
    bool pointyTop = rand() % 2;
    makeColumn(basePoints[i], height, splitPoint, growOutAmount, true);
  }
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build
// your shape!
void Triangle::insertVec3(std::vector<float> &data, glm::vec3 v) {
  data.push_back(v.x);
  data.push_back(v.y);
  data.push_back(v.z);
}
