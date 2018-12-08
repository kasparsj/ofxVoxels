#include "Plane.hpp"
#include "ofMain.h"

using namespace vxls;

int Plane::numInstances = 0;

void Plane::setupParameterGroup() {
    Symbol::setupParameterGroup();
    pNumNodes.set("Nodes", glm::vec4(1), glm::vec4(1), glm::vec4(50, 50, 1, 1));
    pColor.set("NodeColor", ofColor::white);
    pNumColors.set("NumNodeColors", 1, 1, 1000);
    pNodeSize.set("NodeSize", glm::vec3(5000, 1, 5000), glm::vec3(1), glm::vec3(10000));
    pNodeSpacing.set("NodeSpacing", glm::vec3(0), glm::vec3(-100), glm::vec3(200));
}
