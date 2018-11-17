#include "Cross.hpp"

using namespace ofxVoxels;

int Cross::numInstances = 0;

void Cross::transform() {
    this->registration = pReg.get();
    this->nodeSize = glm::vec3(pNodeSize.get());
    this->nodeSpacing = glm::vec3(pNodeSpacing.get());
    this->nodeDisplacement = pNodeDisplacement.get();
    updateDims();
    for (int x=0; x<numNodes.x; x++) {
        const shared_ptr<Node> &box = nodes[x];
        float boxX = (-numNodes.x/2 + x) * (nodeSize.x + nodeSpacing.x);
        float boxY = 0;
        float boxZ = 0;
        box->setPosition(origin+glm::vec3(boxX, boxY, boxZ));
        box->setScale(nodeSize);
    }
    for (int y=0; y<numNodes.y; y++) {
        const shared_ptr<Node> &box = nodes[numNodes.x+y];
        float boxX = 0;
        float boxY = (numNodes.y/2 - y) * (nodeSize.y + nodeSpacing.y);
        float boxZ = 0;
        box->setPosition(origin+glm::vec3(boxX, boxY, boxZ));
        box->setScale(nodeSize);
    }
    for (int z=0; z<numNodes.z; z++) {
        const shared_ptr<Node> &box = nodes[numNodes.x+numNodes.y+z];
        float boxX = 0;
        float boxY = 0;
        float boxZ = (numNodes.z/2 - z) * (nodeSize.z + nodeSpacing.z);
        box->setPosition(origin+glm::vec3(boxX, boxY, boxZ));
        box->setScale(nodeSize);
    }
}

void Cross::setupParameterGroup() {
    Struct::setupParameterGroup();
    pNumNodes.set("Nodes", ivec4(3, 3, 3, 1), ivec4(1), ivec4(12));
    pColor.set("NodeColor", ofColor::white);
    pNumColors.set("NumNodeColors", 1, 1, 1000);
    pNodeSpacing.set("NodeSpacing", 0, -100, 200);
}
