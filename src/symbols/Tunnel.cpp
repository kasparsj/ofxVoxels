#include "Tunnel.hpp"

using namespace vxls;

int Tunnel::numInstances = 0;

void Tunnel::setupParameterGroup() {
    Symbol::setupParameterGroup();
    pNumNodes.set("Nodes", glm::vec4(12, 12, 50, 1), glm::vec4(1), glm::vec4(24, 24, 100, 1));
    pGroup.add(pCircular.set("Circular", false));
}
