#pragma once

#include "Container.hpp"
#include "ofParameter.h"
#include "ColorWheelSchemes.h"

namespace ofxVoxels {
    
    using namespace std;
    using namespace glm;
    using namespace ofxColorTheory;
    
    class Struct : public Container {
        
    public:
        Struct() {
            ofxVecExpr<glm::vec3>* lNodeProps[3] = {&lNodeSize, &lNodeSpacing, &lNodeDisplacement};
            for (int i=0; i<3; i++) {
                lNodeProps[i]->add_var("x", curX);
                lNodeProps[i]->add_var("y", curY);
                lNodeProps[i]->add_var("z", curZ);
                lNodeProps[i]->add_var("t", curTime);
            }
        }
        virtual void resize(const vec4 &numNodes);
        virtual void setupParameterGroup();
        virtual void transform() = 0;
        virtual void setColors(const vector<ofColor> & colors);
        void initRotation(vec3 maxSpeed = ofVec3f(1.f), float rotation = 0.f);
        virtual void update(const glm::mat4 &mat);
        virtual void updateFromParams();
        virtual void randomize();
        virtual void randomizeColor();
        virtual int countNodes() {
            return numNodes.x * numNodes.y * numNodes.z;
        }        
        int index(int x, int y, int z) {
            return (z * numNodes.x * numNodes.y) + (y * numNodes.x) + x;
        }
        const shared_ptr<Node> &getNode(int x, int y, int z) {
            return Object::getNode(index(x, y, z));
        }
        float noise(float x) {
            return ofNoise(noiseOffset.x + (x * noiseMult));
        }
        float noise(float x, float y) {
            return ofNoise(vec2(noiseOffset) + vec2(x * noiseMult, y * noiseMult));
        }
        float noise(float x, float y, float z) {
            return ofNoise(noiseOffset + vec3(x * noiseMult, y * noiseMult, z * noiseMult));
        }
        float noise(const glm::vec3 &xyz) {
            return noise(xyz.x, xyz.y, xyz.z);
        }
        virtual bool isTransformDirty() {
            return pReg.get() != lReg ||
                   pNodeSize.get() != lNodeSize ||
                   pNodeSpacing.get() != lNodeSpacing ||
                   pNodeDisplacement.get() != lNodeDisplacement;
        }
        virtual void updateDims();
        virtual const glm::mat4 getChildMatrix(const Container *child) const {
            return sidesMatrix[(int)child->getSide()];
        }
        void setNumColors(int value) {
            pNumColors.set(value);
        }
        void setNoiseMult(float value) {
            pNoise.set(value);
        }
        void setNoiseAnim(float value) {
            pNoiseAnim.set(value);
        }
        
    protected:
        void updateColors();

        int lReg;
        vector<glm::mat4> sidesMatrix;
        glm::ivec4 numNodes;
        ofxVecExpr<glm::vec3> lNodeSize;
        ofxVecExpr<glm::vec3> lNodeSpacing;
        ofxVecExpr<glm::vec3> lNodeDisplacement;
        float noiseMult = 0;
        glm::vec3 noiseOffset;
        glm::vec3 noiseAnimOffset;
        shared_ptr<ColorWheelScheme> scheme;
        
        ofParameter<float> pColorScheme;
        ofParameter<int> pNumColors;
        ofParameter<float> pNoise;
        ofParameter<float> pNoiseAnim;
        
        float curX, curY, curZ, curTime;
        
    };
    
}
