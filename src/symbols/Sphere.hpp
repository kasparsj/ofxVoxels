#pragma once

#include "Symbol.hpp"

namespace vxls {
    
    class Sphere : public Symbol {
        
    public:
        virtual std::string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Sphere " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        const glm::vec3 posNormal(const glm::ivec3 &idx) const {
            float theta = idx.x * (TWO_PI / numNodes.x);
            float phi = idx.z * (TWO_PI / numNodes.z);
            float rx = (numNodes.x-1) / 2.f;
            float ry = (numNodes.y-1) / 2.f;
            float rz = (numNodes.z-1) / 2.f;
            float boxX = rx * cos(theta) * sin(phi);
            float boxY = ry * sin(theta) * sin(phi);
            float boxZ = rz * cos(phi);
            return glm::vec3(boxX, boxY, boxZ);
        }
        
    private:
        static int numInstances;
        
    };
    
}
