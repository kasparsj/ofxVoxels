#pragma once

#include "Container.hpp"
#include "ofParameter.h"
#include "ColorWheelSchemes.h"

namespace vxls {
    
    class Struct : public Container {
        
    public:
        Struct() {
            lNumNodes.setName("lNumNodes");
            lNodeSize.setName("lNodeSize");
            lNodeSpacing.setName("lNodeSpacing");
            lNodeDisplacement.setName("lNodeDisplacement");
            lNumNodes.addVar("t", curTime);
            ofxVecExpr<glm::vec3>* lNodeProps[3] = {&lNodeSize, &lNodeSpacing, &lNodeDisplacement};
            for (int i=0; i<3; i++) {
                lNodeProps[i]->addVar("x", curX, false);
                lNodeProps[i]->addVar("y", curY, false);
                lNodeProps[i]->addVar("z", curZ, false);
                lNodeProps[i]->addVar("t", curTime);
            }
            ofxVecExpr<glm::vec3>* pNodeProps[3] = {&pNodeSize, &pNodeSpacing, &pNodeDisplacement};
            for (int i=0; i<3; i++) {
                pNodeProps[i]->addDummyVar("x");
                pNodeProps[i]->addDummyVar("y");
                pNodeProps[i]->addDummyVar("z");
                pNodeProps[i]->addDummyVar("t");
            }
        }
        virtual void resize();
        virtual void setupParameterGroup();
        virtual void transform() = 0;
        virtual void setColors(const std::vector<ofColor> & colors);
        void initRotation(glm::vec3 maxSpeed = ofVec3f(1.f), float rotation = 0.f);
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
        const std::shared_ptr<Node> &getNode(int x, int y, int z) {
            return Object::getNode(index(x, y, z));
        }
        float noise(float x) {
            return ofNoise(noiseOffset.x + (x * noiseMult));
        }
        float noise(float x, float y) {
            return ofNoise(glm::vec2(noiseOffset) + glm::vec2(x * noiseMult, y * noiseMult));
        }
        float noise(float x, float y, float z) {
            return ofNoise(noiseOffset + glm::vec3(x * noiseMult, y * noiseMult, z * noiseMult));
        }
        float noise(const glm::vec3 &xyz) {
            return noise(xyz.x, xyz.y, xyz.z);
        }
        virtual bool isTransformDirty() {
            return pReg.get() != lReg ||
                   pNodeSize != lNodeSize || lNodeSize.hasExprSymbol("t") ||
                   pNodeSpacing != lNodeSpacing || lNodeSpacing.hasExprSymbol("t") ||
                   pNodeDisplacement != lNodeDisplacement || lNodeDisplacement.hasExprSymbol("t");
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
        std::vector<glm::mat4> sidesMatrix;
        glm::ivec4 numNodes;
        ofxVecExpr<glm::vec4> lNumNodes;
        ofxVecExpr<glm::vec3> lNodeSize;
        ofxVecExpr<glm::vec3> lNodeSpacing;
        ofxVecExpr<glm::vec3> lNodeDisplacement;
        float noiseMult = 0;
        glm::vec3 noiseOffset;
        glm::vec3 noiseAnimOffset;
        std::shared_ptr<ofxColorTheory::ColorWheelScheme> scheme;
        
        ofParameter<float> pColorScheme;
        ofParameter<int> pNumColors;
        ofParameter<float> pNoise;
        ofParameter<float> pNoiseAnim;
        
        float curX, curY, curZ, curTime;
        
    };
    
}
