#pragma once

#include "Symbol.hpp"

namespace vxls {
    
    class Cross : public Symbol {
        
    public:
        virtual std::string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Cross " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual int countNodes() {
            return numNodes.x + numNodes.y + numNodes.z - 2;
        }
        virtual int pack(const int x, const int y, const int z) const {
            if (z > 0) {
                return numNodes.x + numNodes.y + z - 2;
            }
            if (y > 0) {
                return numNodes.x + y - 1;
            }
            return x;
        }
        const glm::ivec3 unpack(const int index) const {
            int x = 0; int y = 0; int z = 0;
            if (index < numNodes.x) {
                return glm::ivec3(index, 0, 0);
            }
            else if ((index + 1) < numNodes.x + numNodes.y) {
                return glm::ivec3(0, (index + 1) - numNodes.x, 0);
            }
            return glm::ivec3(0, 0, (index + 2) - (numNodes.x + numNodes.y));
        }
        virtual const glm::vec3 posNormal(const glm::ivec3 &idx) const {
            return glm::vec3(idx.x > numNodes.x/2 ? numNodes.x/2 - idx.x : idx.x,
                             idx.y > numNodes.y/2 ? numNodes.y/2 - idx.y : idx.y,
                             idx.z > numNodes.z/2 ? numNodes.z/2 - idx.z : idx.z);
        }
        virtual void setupParameterGroup();
      
    private:
        static int numInstances;
        
    };
    
}
