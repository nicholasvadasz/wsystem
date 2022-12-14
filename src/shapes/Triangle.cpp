#include "Triangle.h"
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <map>
#include <stdlib.h>
#define NUM_COLUMNS 10

void Triangle::updateParams(int param1, int param2, int param3, int param4) {
  m_vertexData = std::vector<float>();
  m_param1 = param1;
  m_param2 = param2;
  m_param3 = param3;
  m_param4 = param4;
  if (randomSeedValues.size() == 0) {
    triggerSeedChange();
  } else {
    justTheVertices.clear();
    setVertexData();
  }
}

void Triangle::triggerSeedChange() {
  randomSeedValues = std::vector<std::vector<uint32_t>>();
  for (int i = 0; i < NUM_COLUMNS; i++) {
    std::vector<uint32_t> seedValues;
    for (int j = 0; j < 8; j++) {
      seedValues.push_back(arc4random());
    }
    randomSeedValues.push_back(seedValues);
  }
  justTheVertices.clear();
  m_vertexData.clear();
  setVertexData();
}

void Triangle::makeTile(glm::vec3 topLeft, glm::vec3 topRight,
                        glm::vec3 bottomLeft, glm::vec3 bottomRight) {
  glm::vec3 CA1 = bottomRight - bottomLeft;
  glm::vec3 CB1 = topLeft - bottomLeft;
  glm::vec3 normal1 = glm::normalize(glm::cross(CA1, CB1));
  insertVec3(m_vertexData, bottomLeft);
  justTheVertices.push_back(bottomLeft);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, bottomRight);
  justTheVertices.push_back(bottomRight);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, topLeft);
  justTheVertices.push_back(topLeft);
  insertVec3(m_vertexData, normal1);
  glm::vec3 CA2 = topRight - topLeft;
  glm::vec3 CB2 = bottomRight - topLeft;
  glm::vec3 normal2 = glm::normalize(glm::cross(CB2, CA2));
  insertVec3(m_vertexData, topLeft);
  justTheVertices.push_back(topLeft);
  insertVec3(m_vertexData, normal2);
  insertVec3(m_vertexData, bottomRight);
  justTheVertices.push_back(bottomRight);
  insertVec3(m_vertexData, normal2);
  insertVec3(m_vertexData, topRight);
  justTheVertices.push_back(topRight);
  insertVec3(m_vertexData, normal2);
}

void Triangle::makeTriangle(glm::vec3 bottomLeft, glm::vec3 bottomRight,
                            glm::vec3 top) {
  glm::vec3 CA1 = bottomRight - bottomLeft;
  glm::vec3 CB1 = top - bottomLeft;
  glm::vec3 normal1 = glm::normalize(glm::cross(CA1, CB1));
  normal1 = -normal1;
  insertVec3(m_vertexData, bottomRight);
  justTheVertices.push_back(bottomRight);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, bottomLeft);
  justTheVertices.push_back(bottomLeft);
  insertVec3(m_vertexData, normal1);
  insertVec3(m_vertexData, top);
  justTheVertices.push_back(top);
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
  tempTopBasePoints.push_back(topPoints);
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
  // first, create an lsystem that draws a series of lines
  std::string axiom = "F";
  std::map<char, std::string> rules;
  rules['F'] = "F+G";
  rules['G'] = "F-G";
  glm::vec2 start = glm::vec2(0.0f, 0.0f); // this is on the (x, z) plane
  float length = .2f;
  for (int i = 0; i < 4; i++) {
    std::string newAxiom = "";
    for (int j = 0; j < axiom.length(); j++) {
      if (rules.find(axiom[j]) != rules.end()) {
        newAxiom += rules[axiom[j]];
      } else {
        newAxiom += axiom[j];
      }
    }
    axiom = newAxiom;
  }
  std::cout << axiom << std::endl;
  std::vector<line> lines = std::vector<line>();
  glm::vec2 currentPos = start;
  glm::vec2 currentDir = glm::vec2(0.0f, 1.0f);
  for (int i = 0; i < axiom.length(); i++) {
    if (axiom[i] == 'F') {
      glm::vec2 newPos = currentPos + currentDir * length;
      lines.push_back(line{currentPos, newPos});
      currentPos = newPos;
    } else if (axiom[i] == '+') {
      // rotate 90 degrees clockwise
      if (currentDir.x == 0.0f) {
        if (currentDir.y == 1.0f) {
          currentDir = glm::vec2(1.0f, 0.0f);
        } else {
          currentDir = glm::vec2(-1.0f, 0.0f);
        }
      } else {
        if (currentDir.x == 1.0f) {
          currentDir = glm::vec2(0.0f, -1.0f);
        } else {
          currentDir = glm::vec2(0.0f, 1.0f);
        }
      }
    } else if (axiom[i] == '-') {
      if (currentDir.x == 0.0f) {
        if (currentDir.y == 1.0f) {
          currentDir = glm::vec2(-1.0f, 0.0f);
        } else {
          currentDir = glm::vec2(1.0f, 0.0f);
        }
      } else {
        if (currentDir.x == 1.0f) {
          currentDir = glm::vec2(0.0f, 1.0f);
        } else {
          currentDir = glm::vec2(0.0f, -1.0f);
        }
      }
    } else if (axiom[i] == 'G') {
      glm::vec2 newPos = currentPos + currentDir * length;
      lines.push_back(line{currentPos, newPos});
      currentPos = newPos;
    }
  }
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i].start.x != lines[i].end.x) {
      // we know x is the on changing, so we use this to offset the points when
      // making the column
      // makeTile(glm::vec3(lines[i].end.x, 0.0f, lines[i].end.y),
      //          glm::vec3(lines[i].end.x, 0.0f, lines[i].end.y + .1f),
      //          glm::vec3(lines[i].start.x, 0.0f, lines[i].start.y),
      //          glm::vec3(lines[i].start.x, 0.0f, lines[i].start.y + .1f));
      std::vector<glm::vec3> points = std::vector<glm::vec3>();
      points.push_back(glm::vec3(lines[i].end.x, 0.0f, lines[i].end.y + .1f));
      points.push_back(glm::vec3(lines[i].end.x, 0.0f, lines[i].end.y));
      points.push_back(glm::vec3(lines[i].start.x, 0.0f, lines[i].start.y));
      points.push_back(
          glm::vec3(lines[i].start.x, 0.0f, lines[i].start.y + .1f));
      makeColumn(points, .1f, 1.0f, 0, false);
    } else {
      // std::vector<glm::vec3> points = std::vector<glm::vec3>();
      // points.push_back(glm::vec3(lines[i].end.x, 0.0f, lines[i].end.y));
      // points.push_back(glm::vec3(lines[i].end.x + .1f, 0.0f,
      // lines[i].end.y)); points.push_back(
      //     glm::vec3(lines[i].start.x + .1f, 0.0f, lines[i].start.y));
      // points.push_back(glm::vec3(lines[i].start.x, 0.0f, lines[i].start.y));
      // makeColumn(points, .1f, 1.0f, 0, false);
    }
  }
  // set topBasePoints to be whatever is currently in tempTopBasePoints
  topBasePoints = tempTopBasePoints;
  for (int i = 0; i < 5; i++) {
    // push every single x value in topBasePoints .1f in the positive x
    // direction
    for (int j = 0; j < topBasePoints.size(); j++) {
      for (int k = 0; k < topBasePoints[j].size(); k++) {
        topBasePoints[j][k].x += .1f;
        topBasePoints[j][k].z += .1f;
      }
    }
    // clear tempTopBasePoints
    tempTopBasePoints.clear();
    // make a new column for every point in topBasePoints
    for (int j = 0; j < topBasePoints.size(); j++) {
      makeColumn(topBasePoints[j], .1f, 1.0f, 0, false);
    }
    // set topBasePoints to be whatever is currently in tempTopBasePoints
    topBasePoints = tempTopBasePoints;
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
