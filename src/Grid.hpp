#pragma once

#include "Struct.hpp"
#include "ofColor.h"

using namespace std;

namespace ofxVoxels {
    
    class Grid : public Struct {
        
    public:
        virtual string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Grid " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        virtual void transform();
        void write(int res, int z, vector<ofColor> & colors);
        void shiftColor(int x, int y);
        
    private:
        static int numInstances;
        
    };
    
}