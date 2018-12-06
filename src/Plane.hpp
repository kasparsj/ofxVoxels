#pragma once

#include "Struct.hpp"

namespace vxls {
    
    class Plane : public Struct {
        
    public:
        virtual std::string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Plane " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual void setupParameterGroup();
                
    private:
        static int numInstances;
        
    };
    
}
