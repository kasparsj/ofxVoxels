#pragma once

#include "Container.hpp"
#include "ofParameter.h"
#include "ColorWheelSchemes.h"

namespace vxls {
    
    class Struct : public Container {
        
    public:
        Struct() {
            lPos.setName("lPos");
            lPos.addVar("t", curTime);
            pPos.addDummyVar("t");
            lNumNodes.setName("lNumNodes");
            lNodeSize.setName("lNodeSize");
            lNodeSpacing.setName("lNodeSpacing");
            lNodeDisplacement.setName("lNodeDisplacement");
            lNumNodes.addVar("t", curTime);
            pNumNodes.addDummyVar("t");
            ofxVecExpr<glm::vec3>* lNodeProps[3] = {&lNodeSize, &lNodeSpacing, &lNodeDisplacement};
            for (int i=0; i<3; i++) {
                lNodeProps[i]->addVar("x", posX, false);
                lNodeProps[i]->addVar("y", posY, false);
                lNodeProps[i]->addVar("z", posZ, false);
                lNodeProps[i]->addVar("t", curTime);
            }
            ofxVecExpr<glm::vec3>* pNodeProps[3] = {&pNodeSize, &pNodeSpacing, &pNodeDisplacement};
            for (int i=0; i<3; i++) {
                pNodeProps[i]->addDummyVar("x", false);
                pNodeProps[i]->addDummyVar("y", false);
                pNodeProps[i]->addDummyVar("z", false);
                pNodeProps[i]->addDummyVar("t");
            }
        }
        virtual void resize();
        virtual void transform();
        virtual void animate();
        virtual void setColors(const std::vector<ofColor> & colors);
        void initRotation(glm::vec3 maxSpeed = ofVec3f(1.f), float rotation = 0.f);
        virtual void update(const glm::mat4 &mat);
        virtual void updateFromParams();
        virtual void randomize();
        virtual void randomizeColor();
        virtual void setupParameterGroup();
        virtual int countNodes() {
            return numNodes.x * numNodes.y * numNodes.z;
        }
        virtual int pack(const int x, const int y, const int z) const {
            return (z * numNodes.x * numNodes.y) + (y * numNodes.x) + x;
        }
        virtual const glm::ivec3 unpack(const int index) const {
            int z = index / (numNodes.x * numNodes.y);
            int i = index - (z * (numNodes.x * numNodes.y));
            int y = i / numNodes.x;
            int x = i - (y * numNodes.x);
            return glm::ivec3(x, y, z);
            
        }
        virtual const glm::vec3 posNormal(const glm::ivec3 &idx) const {
            return glm::vec3((-numNodes.x+1)/2.f + idx.x,
                             (numNodes.y-1)/2.f - idx.y,
                             (numNodes.z-1)/2.f - idx.z);
        }
        const std::shared_ptr<Node> &getNode(int x, int y, int z) {
            return Object::getNode(pack(x, y, z));
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
                   pNodeSize != lNodeSize ||
                   pNodeSpacing != lNodeSpacing ||
                   pNodeDisplacement != lNodeDisplacement;
        }
        virtual bool isTransformAnim() {
            return lNodeSize.hasExprSymbol("t") ||
                   lNodeSpacing.hasExprSymbol("t") ||
                   lNodeDisplacement.hasExprSymbol("t");
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
        void setCurrentNode(const int index);
        void updateCurrentNode();
        const glm::vec3 getNodePosition() const;
        const glm::vec3 getNodeScale() const;
        
    protected:
        void updateColors();

        int lReg;
        std::vector<glm::mat4> sidesMatrix;
        glm::ivec4 numNodes;
        ofxVecExpr<glm::vec3> lPos;
        ofxVecExpr<glm::vec4> lNumNodes;
        ofxVecExpr<glm::vec3> lNodeSize;
        ofxVecExpr<glm::vec3> lNodeSpacing;
        ofxVecExpr<glm::vec3> lNodeDisplacement;
        std::vector<glm::vec3> explicitNodeDisplacement;
        float noiseMult = 0;
        glm::vec3 noiseOffset;
        glm::vec3 noiseAnimOffset;
        std::shared_ptr<ofxColorTheory::ColorWheelScheme> scheme;
        
        ofParameter<float> pColorScheme;
        ofParameter<int> pNumColors;
        ofParameter<float> pNoise;
        ofParameter<float> pNoiseAnim;
        
        float posX, posY, posZ, curTime, curIdx;
        
        std::shared_ptr<Node> currentNode;
        
    };
    
}
