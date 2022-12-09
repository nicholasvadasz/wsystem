#pragma once

#include <glm/glm.hpp>
#include <vector>

class Cylinder {
public:
  void updateParams(int param1, int param2);
  std::vector<float> generateShape() { return m_vertexData; }

private:
  void insertVec3(std::vector<float> &data, glm::vec3 v);
  void setVertexData();
  void makeTileSide(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft,
                    glm::vec3 bottomRight);
  void makeTileTopOrBot(glm::vec3 topLeft, glm::vec3 topRight,
                        glm::vec3 bottomLeft, glm::vec3 bottomRight,
                        glm::vec3 normal);
  void makeWedge(float currentTheta, float nextTheta);

  std::vector<float> m_vertexData;
  int m_param1;
  int m_param2;
  float m_radius = 0.5;
};
