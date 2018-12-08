#pragma once

#include "Symbol.hpp"
#include "ofColor.h"

using namespace std;

namespace vxls {
    
    class Grid : public Symbol {
        
    public:
        virtual string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Grid " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        void write(int res, int z, vector<ofColor> & colors);
        void shiftColor(int x, int y);
        
    private:
        static int numInstances;
        
    };
    
}
