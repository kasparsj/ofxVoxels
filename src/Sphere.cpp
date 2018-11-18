#include "Sphere.hpp"

using namespace ofxVoxels;

int Sphere::numInstances = 0;

void Sphere::transform() {
    lReg = pReg.get();
    lNodeSize = pNodeSize.get();
    lNodeSpacing = pNodeSpacing.get();
    lNodeDisplacement = pNodeDisplacement.get();
    updateDims();
    for (int x=0; x<numNodes.x; x++) {
        for (int y=0; y<numNodes.y; y++) {
            for (int z=0; z<numNodes.z; z++) {
                curX = x; curY = y; curZ = z;
                glm::vec3 nodeSize = lNodeSize.value();
                glm::vec3 nodeSpacing = lNodeSpacing.value();
                glm::vec3 nodeDisplacement = lNodeDisplacement.value();
                int i = index(x, y, z);
                const shared_ptr<Node> &box = nodes[i];
                float theta = x * (TWO_PI / numNodes.x);
                float phi = z * (TWO_PI / numNodes.z);
                float rx = (((numNodes.x-1)/2.f) * (nodeSize.x + nodeSpacing.x));
                float ry = (((numNodes.y-1)/2.f) * (nodeSize.y + nodeSpacing.y));
                float rz = (((numNodes.z-1)/2.f) * (nodeSize.z + nodeSpacing.z));
                float boxX = rx * cos(theta) * sin(phi);
                float boxY = ry * sin(theta) * sin(phi);
                float boxZ = rz * cos(phi);
                box->setPosition(origin + glm::vec3(boxX, boxY, boxZ));
                box->setScale(nodeSize);
            }
        }
    }
}
