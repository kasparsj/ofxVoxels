#pragma once

#include "Struct.hpp"

namespace vxls {
    
    class Sphere : public Struct {
        
    public:
        virtual std::string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Sphere " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual void transform();
        
    private:
        static int numInstances;
        
    };
    
}
