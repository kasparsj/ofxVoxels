#include "Plane.hpp"
#include "ofMain.h"

using namespace ofxVoxels;

int Plane::numInstances = 0;

void Plane::transform() {
    this->registration = pReg.get();
    this->nodeSize = glm::vec3(pNodeSize.get());
    this->nodeSpacing = glm::vec3(pNodeSpacing.get());
    this->nodeDisplacement = pNodeDisplacement.get();
    updateDims();
    for (int x=0; x<numNodes.x; x++) {
        for (int y=0; y<numNodes.y; y++) {
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
    pNodeSize.set("NodeSize", 5000, 1, 10000);
    pNodeSpacing.set("NodeSpacing", 0, -100, 200);
}
