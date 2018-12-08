#pragma once

#include "ofColor.h"
#include "ofParameter.h"
#include "ofMath.h"

namespace vxls {
    
    class HasColor {
        
    public:
        const ofColor &getColor() {
            return pColor.get();
        }
        virtual void setColor(ofColor color) {
            pColor.set(color);
        }
        virtual void randomizeColor() {
            setColor(ofFloatColor(ofRandom(1.f), ofRandom(1.f), ofRandom(1.f)));
        }
        
    protected:
        ofParameter<ofColor> pColor;
        
    };
    
}
