#pragma once

#include <glm/glm.hpp>
#include <vector>

class Triangle {
public:
  void updateParams(int param1, int param2, int param3, int param4);
  std::vector<glm::vec3> basePoints;
  std::vector<float> generateShape() { return m_vertexData; }
  void triggerSeedChange();
  std::vector<glm::vec3> justTheVertices;
  std::vector<glm::vec3> getJustTheVertices() { return justTheVertices; }
  std::vector<std::vector<uint32_t>> getSeedValues() {
    return randomSeedValues;
  }

private:
  void makeTriangle(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 top);
  void makeTile(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                glm::vec3 bottomRight);
  void makeColumn(std::vector<glm::vec3> basePoints, float height,
                  float splitPoint, float growOutAmount, bool pointyTop);
  void insertVec3(std::vector<float> &data, glm::vec3 v);
  void setVertexData();

  std::vector<float> m_vertexData;
  std::vector<std::vector<uint32_t>> randomSeedValues;
  int m_param1;
  int m_param2;
  int m_param3;
  int m_param4;
};
