#pragma once

#include <glm/glm.hpp>
#include <vector>

class Triangle {
public:
  void updateParams(int param1, int param2, int param3, int param4, bool useHex);
  std::vector<glm::vec3> basePoints;
  std::vector<float> generateShape() { return m_vertexData; }
  void triggerSeedChange();
  std::vector<glm::vec3> justTheVertices;
  std::vector<glm::vec3> getJustTheVertices() { return justTheVertices; }
  std::vector<std::vector<uint32_t>> getSeedValues() {
    return randomSeedValues;
  }
  struct normal {
    int normalID;
    glm::vec3 n;
  };

  struct vertex {
    int vertexID;
    glm::vec3 v;
    normal n;
  };

  struct face {
      std::vector<vertex> vertexVector;
      float size = 1.0f;
      normal n;
      glm::vec3 loc;
  };
  std::vector<Triangle::face> allHexagonFaces;

private:
  void makeTriangle(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 top);
  void makeTile(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                glm::vec3 bottomRight);
  void makeColumn(std::vector<glm::vec3> basePoints, float height,
                  float splitPoint, float growOutAmount, bool pointyTop);
  void insertVec3(std::vector<float> &data, glm::vec3 v);
  void setVertexData();
  void setHexagonData();

  void makeHexagon(float xPos, float yPos, float size);
  void importancePoint(float severityRatio, float height, float maxScale);
  void makeHexTriangle(glm::vec3 pos1, glm::vec3 norm1, glm::vec3 pos2, glm::vec3 norm2, glm::vec3 pos3, glm::vec3 norm3);

  std::vector<float> m_vertexData;
  std::vector<std::vector<uint32_t>> randomSeedValues;
  int m_param1;
  int m_param2;
  int m_param3;
  int m_param4;
  bool m_useHex;
};
