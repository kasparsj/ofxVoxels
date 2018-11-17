#pragma once

#include "Struct.hpp"

namespace ofxVoxels {
    
    class Cross : public Struct {
        
    public:
        virtual string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Cross " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual int countNodes() {
            return numNodes.x + numNodes.y + numNodes.z;
        }
        virtual void transform();
        virtual void setupParameterGroup();
      
    private:
        static int numInstances;
        
    };
    
}