#include "Tunnel.hpp"

using namespace ofxVoxels;

int Tunnel::numInstances = 0;

void Tunnel::transform() {
    lReg = pReg.get();
    lNodeSize = pNodeSize.get();
    lNodeSpacing = pNodeSpacing.get();
    lNodeDisplacement = pNodeDisplacement.get();
    updateDims();
    int boxesXY = (numNodes.x+numNodes.y) * 2;
    for (int z=0; z<numNodes.z; z++) {
        for (int xy=0; xy<boxesXY; xy++) {
            curZ = z;
            glm::vec3 nodeSize = lNodeSize.value();
            glm::vec3 nodeSpacing = lNodeSpacing.value();
            glm::vec3 nodeDisplacement = lNodeDisplacement.value();
            int i = (z * boxesXY) + xy;
            const shared_ptr<Node> &box = nodes[i];
            float boxX;
            float boxY;
            float theta = xy * (TWO_PI / boxesXY);
            float rx = (((numNodes.x-1)/2.f) * (nodeSize.x + nodeSpacing.x));
            float ry = (((numNodes.y-1)/2.f) * (nodeSize.y + nodeSpacing.y));
            if (pCircular.get() == 1) {
                boxX = rx * cos(theta);
                boxY = ry * sin(theta);
            }
            else {
                float QUARTER_PI = HALF_PI / 2.f;
                // north
                boxX = tan(theta-HALF_PI) * rx;
                boxY = -ry;
                // east
                if (theta > TWO_PI-QUARTER_PI || theta < QUARTER_PI) {
                    boxX = rx;
                    boxY = tan(theta) * ry;
                }
                // south
                if(theta >= QUARTER_PI && theta < QUARTER_PI+HALF_PI) {
                    boxX = -tan(theta-HALF_PI)*rx;
                    boxY = ry;
                }
                // west
                if(theta >= HALF_PI+QUARTER_PI && theta < PI+QUARTER_PI) {
                    boxX = -rx;
                    boxY = -tan(theta)*ry;
                }
            }
            box->setPosition(origin + glm::vec3(boxX, boxY, (numNodes.z/2 - z) * (nodeSize.z + nodeSpacing.z)) + nodeDisplacement);
            box->setScale(nodeSize);
        }
    }
}

void Tunnel::setupParameterGroup() {
    Struct::setupParameterGroup();
    pNumNodes.set("Nodes", ivec4(12, 12, 50, 1), ivec4(1), ivec4(24, 24, 100, 1));
    pGroup.add(pCircular.set("Circular", false));
}
