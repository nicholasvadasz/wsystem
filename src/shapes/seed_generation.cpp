#include "Triangle.h"
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <stdlib.h>
#define NUM_COLUMNS 10
int randUp;
void Triangle::setHexagonData() {
    randUp = 0;
    allHexagonFaces.clear();
    float radius = 2.0f/(2.0f * m_param4);
    for (int x = -m_param4/2 + 1; x < m_param4/2; x++)
    {
        for (int y = -m_param4 + 1; y < m_param4; y++)
        {
            float xPos = ((x* 3.0 * radius) + ((y % 2) * 1.5f * radius));
            float yPos = y * radius * 0.875f;
            if(glm::distance(glm::vec2(xPos,yPos), glm::vec2(0.0, 0.0)) < 1.0f){
                makeHexagon(xPos, yPos, radius);
            }
        }
    }

    importancePoint(1.5,0.3,2.0);
    importancePoint(0.8,0.2,1);
    importancePoint(0.5,0.5,2.5f);
    importancePoint(0.5,0.5,2.5f);
    importancePoint(0.5,0.5,2.5f);

    for(face currFace: allHexagonFaces){

        for(int i = 0; i < 6; i ++){
            int endLoc = i + 1;
            if(endLoc == 6){
                endLoc = 0;
            }
            //std::cout << "when assigning to actual data structures, my y is " << currFace.vertexVector[i].v.y << std::endl;

            makeHexTriangle(currFace.vertexVector[i].v, currFace.n.n,
                         currFace.loc, currFace.n.n,
                         currFace.vertexVector[endLoc].v, currFace.n.n);
        }
    }
}

void Triangle::importancePoint(float severityRatio, float height, float maxScale){
    srand ( time(NULL) + rand() );
    float rand1 = rand() % 360;
    float rand2 = (rand() % 100)/100.0f;
    float randomAngle = glm::radians(rand1);
    float randomLength = rand2/2.0f;
    float range = 0.9f * severityRatio;
    float pointX = randomLength * cos(randomAngle);
    float pointY = 0.2;
    float pointZ = randomLength * sin(randomAngle);
    float raisePoint = height;
    float scale = 1.25 + (rand2/5) * (1.0f/severityRatio) * maxScale;

    for(int j = 0; j < allHexagonFaces.size(); j++){//face currFace: allHexagonFaces){
        allHexagonFaces[j].loc = glm::vec3(0.0,0.0,0.0);
        for(int i = 0; i < 6; i ++){
            vertex currVertex = allHexagonFaces[j].vertexVector[i];
            normal currNormal = currVertex.n;
            glm::vec4 thisPoint = glm::vec4(currVertex.v.x, currVertex.v.y, currVertex.v.z,1.0);
            glm::vec4 thisNormal = glm::vec4(currNormal.n.x, currNormal.n.y, currNormal.n.z,0.0);
            float scaleFalloff = pow(1.0 - (fmin(glm::distance(glm::vec3(thisPoint), glm::vec3(pointX, pointY, pointZ)), range)/range),1.8);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0), glm::vec3((scale * scaleFalloff) + (1.0f - scaleFalloff)));
            auto transformationMatrix = glm::translate(glm::mat4(1.0),glm::vec3(pointX, pointY,pointZ));
            auto raiseMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0.0, raisePoint * scaleFalloff,0.0));

            thisPoint = glm::inverse(transformationMatrix) * raiseMatrix * scaleMatrix * transformationMatrix * thisPoint;
            thisNormal = glm::inverse(transformationMatrix) * raiseMatrix * scaleMatrix * transformationMatrix * thisNormal;

            vertex newVertex;
            normal newNormal;
            newVertex.v = glm::vec3(thisPoint.x, thisPoint.y,thisPoint.z);
            newVertex.n = newNormal;
            newNormal.n = glm::vec3(thisNormal.x,thisNormal.y,thisNormal.z);

            allHexagonFaces[j].vertexVector[i] = newVertex;
            allHexagonFaces[j].loc += newVertex.v;

        }
        allHexagonFaces[j].loc *= 1.0f/6.0f;
        allHexagonFaces[j].n.n = glm::vec3(0.0);


        for(int i = 0; i < 6; i ++){
            glm::vec3 currVertex = allHexagonFaces[j].vertexVector[i].v;
            int nextVertexLoc = i + 1;

            if (nextVertexLoc == 6){
                nextVertexLoc = 0;
            }

            glm::vec3 nextVertex = allHexagonFaces[j].vertexVector[nextVertexLoc].v;

            glm::vec3 centerOfFace = allHexagonFaces[j].loc;

            glm::vec3 U = currVertex -  nextVertex;

            glm::vec3 V = centerOfFace - currVertex;

            allHexagonFaces[j].vertexVector[i].n.n = glm::normalize(glm::cross(U, V));
            allHexagonFaces[j].n.n += allHexagonFaces[j].vertexVector[i].n.n/6.0f;
        }
    }

}


void Triangle::makeHexagon(float xPos, float zPos, float size){

    face newFace;
    newFace.size = ((1.0 - glm::distance(glm::vec2(xPos, zPos), glm::vec2(0,0)))/1.5f) + 0.25f;

    float thetaStep = glm::radians(360.f / 6.0f);
    for (int i = 0; i < 6; i ++){
        vertex newVertex;
        normal newNormal;
        newVertex.v = glm::vec3(xPos + (cos(thetaStep * i) * size), 0.0f, zPos + (sin(thetaStep * i) * size));
        newVertex.n = newNormal;
        newNormal.n = glm::vec3(0.0,1.0,0.0);

        newFace.vertexVector.push_back(newVertex);


        /*makeTriangle(xPos + (cos(thetaStep * i) * size), yPos + (sin(thetaStep * i) * size),
                     xPos, yPos, xPos + (cos(thetaStep * (i + 1)) * size),
                     yPos + (sin(thetaStep * (i + 1)) * size));*/
    }

    newFace.loc = glm::vec3(xPos, 0.0, zPos);
    normal faceNormal;
    faceNormal.n = glm::vec3(0.0,1.0,0.0);
    newFace.n = faceNormal;


    allHexagonFaces.push_back(newFace);
}

void Triangle::makeHexTriangle(glm::vec3 pos1, glm::vec3 norm1, glm::vec3 pos2, glm::vec3 norm2, glm::vec3 pos3, glm::vec3 norm3){
    insertVec3(m_vertexData, glm::vec3{pos1.x,pos1.y,pos1.z});
    insertVec3(m_vertexData, glm::vec3{norm1.x,norm1.y,norm1.z});

    insertVec3(m_vertexData, glm::vec3{pos2.x,pos2.y,pos2.z});
    insertVec3(m_vertexData, glm::vec3{norm2.x,norm2.y,norm2.z});

    insertVec3(m_vertexData, glm::vec3{pos3.x,pos3.y,pos3.z});
    insertVec3(m_vertexData, glm::vec3{norm3.x,norm3.y,norm3.z});

}
