#pragma once

#include <glm/glm.hpp>
#include <vector>

class Cone {
public:
  void updateParams(int param1, int param2);
  std::vector<float> generateShape() { return m_vertexData; }

private:
  void insertVec3(std::vector<float> &data, glm::vec3 v);
  void setVertexData();
  void makeTileSide(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                    glm::vec3 bottomRight, bool isTop);
  void makeTileBot(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                   glm::vec3 bottomRight);
  void makeTip(glm::vec3 tip);

  std::vector<float> m_vertexData;
  int m_param1;
  int m_param2;
  float m_radius = 0.5;
};
