#include "Cross.hpp"

using namespace vxls;

int Cross::numInstances = 0;

void Cross::transform() {
    lReg = pReg.get();
    lNodeSize = pNodeSize;
    lNodeSpacing = pNodeSpacing;
    lNodeDisplacement = pNodeDisplacement;
    updateDims();
    curY = 0;
    curZ = 0;
    for (int x=0; x<numNodes.x; x++) {
        curX = x;
        glm::vec3 nodeSize = lNodeSize.get();
        glm::vec3 nodeSpacing = lNodeSpacing.get();
        glm::vec3 nodeDisplacement = lNodeDisplacement.isExplicit() ? ofRandom(lNodeDisplacement.get()) : lNodeDisplacement.get();
        const std::shared_ptr<Node> &box = nodes[(int)curX];
        float boxX = (-numNodes.x/2 + curX) * (nodeSize.x + nodeSpacing.x);
        box->setPosition(origin+glm::vec3(boxX, 0, 0) + nodeDisplacement);
        box->setScale(nodeSize);
    }
    curX = 0;
    for (int y=0; y<numNodes.y; y++) {
        curY = y;
        glm::vec3 nodeSize = lNodeSize.get();
        glm::vec3 nodeSpacing = lNodeSpacing.get();
        glm::vec3 nodeDisplacement = lNodeDisplacement.isExplicit() ? ofRandom(lNodeDisplacement.get()) : lNodeDisplacement.get();
        const std::shared_ptr<Node> &box = nodes[numNodes.x+(int)curY];
        float boxY = (numNodes.y/2 - curY) * (nodeSize.y + nodeSpacing.y);
        box->setPosition(origin+glm::vec3(0, boxY, 0) + nodeDisplacement);
        box->setScale(nodeSize);
    }
    curY = 0;
    for (int z=0; z<numNodes.z; z++) {
        curZ = z;
        glm::vec3 nodeSize = lNodeSize.get();
        glm::vec3 nodeSpacing = lNodeSpacing.get();
        glm::vec3 nodeDisplacement = lNodeDisplacement.isExplicit() ? ofRandom(lNodeDisplacement.get()) : lNodeDisplacement.get();
        const std::shared_ptr<Node> &box = nodes[numNodes.x+numNodes.y+(int)curZ];
        float boxZ = (numNodes.z/2 - curZ) * (nodeSize.z + nodeSpacing.z);
        box->setPosition(origin+glm::vec3(0, 0, boxZ) + nodeDisplacement);
        box->setScale(nodeSize);
    }
}

void Cross::setupParameterGroup() {
    Struct::setupParameterGroup();
    pNumNodes.set("Nodes", glm::vec4(3, 3, 3, 1), glm::vec4(1), glm::vec4(12));
    pColor.set("NodeColor", ofColor::white);
    pNumColors.set("NumNodeColors", 1, 1, 1000);
    pNodeSpacing.set("NodeSpacing", glm::vec3(0), glm::vec3(-100), glm::vec3(200));
}
