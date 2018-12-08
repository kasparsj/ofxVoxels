#include "Cross.hpp"

using namespace vxls;

int Cross::numInstances = 0;

void Cross::setupParameterGroup() {
    Symbol::setupParameterGroup();
    pNumNodes.set("Nodes", glm::vec4(3, 3, 3, 1), glm::vec4(1), glm::vec4(12));
    pColor.set("NodeColor", ofColor::white);
    pNumColors.set("NumNodeColors", 1, 1, 1000);
    pNodeSpacing.set("NodeSpacing", glm::vec3(0), glm::vec3(-100), glm::vec3(200));
}
