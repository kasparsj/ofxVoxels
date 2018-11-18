#include "Plane.hpp"
#include "ofMain.h"

using namespace ofxVoxels;

int Plane::numInstances = 0;

void Plane::transform() {
    lReg = pReg.get();
    lNodeSize = pNodeSize;
    lNodeSpacing = pNodeSpacing;
    lNodeDisplacement = pNodeDisplacement;
    updateDims();
    curZ = 0;
    for (int x=0; x<numNodes.x; x++) {
        for (int y=0; y<numNodes.y; y++) {
            curX = x; curY = y;
            glm::vec3 nodeSize = lNodeSize.value();
            glm::vec3 nodeSpacing = lNodeSpacing.value();
            glm::vec3 nodeDisplacement = lNodeDisplacement.value();
            int i = index(x, y, 0);
            const shared_ptr<Node> &box = nodes[i];
            float nodeX = (-numNodes.x/2 + x) * (nodeSize.x + nodeSpacing.x);
            float nodeY = (numNodes.y/2 - y) * (nodeSize.y + nodeSpacing.y);
            box->setPosition(origin + glm::vec3(nodeX, nodeY, 0));
            box->setScale(nodeSize);
        }
    }
}

void Plane::setupParameterGroup() {
    Struct::setupParameterGroup();
    pNumNodes.set("Nodes", ivec4(1), ivec4(1), ivec4(50, 50, 1, 1));
    pColor.set("NodeColor", ofColor::white);
    pNumColors.set("NumNodeColors", 1, 1, 1000);
    pNodeSize.set("NodeSize", glm::vec3(5000), glm::vec3(1), glm::vec3(10000));
    pNodeSpacing.set("NodeSpacing", glm::vec3(0), glm::vec3(-100), glm::vec3(200));
}
