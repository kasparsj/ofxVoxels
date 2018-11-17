#pragma once

#include "Struct.hpp"

namespace ofxVoxels {
    
    class Tunnel : public Struct {
      
    public:
        virtual string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Tunnel " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual int countNodes() {
            return ((numNodes.x + numNodes.y) * 2) * numNodes.z;
        }
        virtual void transform();
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
