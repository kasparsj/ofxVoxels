#pragma once

#include "Struct.hpp"

namespace ofxVoxels {
    
    class Plane : public Struct {
        
    public:
        virtual string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Plane " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual void transform();
        virtual void setupParameterGroup();
                
    private:
        static int numInstances;
        
    };
    
}
