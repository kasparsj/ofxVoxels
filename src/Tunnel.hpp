#pragma once

#include "Struct.hpp"

namespace vxls {
    
    class Tunnel : public Struct {
      
    public:
        virtual std::string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Tunnel " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual int countNodes() {
            return ((numNodes.x + numNodes.y) * 2) * numNodes.z;
        }
        virtual int pack(const int x, const int y, const int z) const {
            return (z * (numNodes.x + numNodes.y) * 2) + (y * numNodes.x * 2) + x;
        }
        const glm::ivec3 unpack(const int index) const {
            int z = index / ((numNodes.x + numNodes.y) * 2);
            int i = index - (z * (numNodes.x + numNodes.y) * 2);
            int y = i / (numNodes.x * 2);
            int x = i - (y * numNodes.x * 2);
            return glm::ivec3(x, y, z);
        }
        const glm::vec3 posNormal(const glm::ivec3 &idx) const {
            int xy = (idx.y * numNodes.x * 2) + idx.x;
            int boxesXY = (numNodes.x + numNodes.y) * 2;
            float theta = ((float) xy / (float) boxesXY) * TWO_PI;
            float boxX;
            float boxY;
            float rx = (numNodes.x-1) / 2.f;
            float ry = (numNodes.y-1) / 2.f;
            if (pCircular.get() == 1) {
                boxX = cos(theta);
                boxY = sin(theta);
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
            return glm::vec3(boxX, boxY, numNodes.z / 2 - idx.z);
        }
        virtual void setupParameterGroup();
        virtual bool isTransformDirty() {
            bool isDirty = Struct::isTransformDirty() || pCircular.get() != circular;
            circular = pCircular.get();
            return isDirty;
        }
        
    private:
        static int numInstances;
        bool circular;
        ofParameter<bool> pCircular;
        
    };
    
}
