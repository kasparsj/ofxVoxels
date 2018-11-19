#pragma once

#include "Container.hpp"
#include "ofVboMesh.h"
#include "ofTexture.h"

namespace vxls {
    
    using namespace std;

    class Stage : public Container {
        
    public:
        Stage();
        virtual string getName() {
            if (pGroup.getName() == "") {
                numInstances++;
                pGroup.setName("Stage " + ofToString(numInstances));
            }
            return pGroup.getName();
        }
        const ofVboMesh & getMesh() const {
            return mesh;
        }
        
        template<class T>
        const shared_ptr<T> addChild(Registration side, Registration reg) {
            return Container::addChild<T>(side, reg);
        }
        
        template<class T>
        const shared_ptr<T> addChild(Registration reg) {
            return Container::addChild<T>(Registration::CENTER, reg);
        }
        
        template<class T>
        const shared_ptr<T> addChild() {
            return addChild<T>(Registration::CENTER, Registration::CENTER);
        }
        
        void update();
        const ofTexture & getTransformTex() const {
            return transformTex;
        }
        const ofTexture & getColorsTex() const {
            return colorsTex;
        }
        
    private:
        ofVboMesh mesh;
        ofTexture transformTex;
        ofBufferObject transformBuffer;
        ofTexture colorsTex;
        ofBufferObject colorsBuffer;

        static int numInstances;
                
    };
    
}
