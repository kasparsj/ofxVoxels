#pragma once

#include "Container.hpp"
#include "ofParameter.h"
#include "ColorWheelSchemes.h"

namespace vxls {
    
    class Symbol : public Container {
        
    public:
        static ofEvent<std::string> added;
        static ofEvent<std::string> removed;
        static Symbol* find(const std::string &name);
        
        Symbol();
        virtual void resize();
        virtual void transform();
        virtual void animate();
        virtual void setColors(const std::vector<ofColor> & colors);
        virtual void update(const glm::mat4 &mat) override;
        virtual void updateFromParams() override;
        virtual void randomize() override;
        virtual void randomizeColor() override;
        virtual void setupParameterGroup() override;
        virtual int countVoxels() const override {
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
        const std::shared_ptr<Voxel> &getVoxel(int x, int y, int z) {
            return VoxelGroup::getVoxel(pack(x, y, z));
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
                   pNodeDisplacement != lNodeDisplacement ||
                   pNodeRotation != lNodeRotation;
        }
        virtual bool isTransformAnim() {
            return lNodeSize.isTimeDependent() ||
                   lNodeSpacing.isTimeDependent() ||
                   lNodeDisplacement.isTimeDependent();
        }
        virtual void updateDims();
        virtual const glm::mat4 getChildMatrix(const Container *child) const override {
            return sidesMatrix[(int)child->getSide()];
        }
        void setColorScheme(int value) {
            pColorScheme.set(value);
        }
        void setNumColors(int value) {
            pNumColors.set(value);
        }
        void setNoiseMult(float value) {
            pNoise.set(value);
        }
        void setNoiseOffset(const glm::vec3 &value) {
            pNoiseOffset.set(value);
        }
        ofxVecExpr<glm::vec3> & getNoiseOffsetExpr() {
            return pNoiseOffset;
        }
        void setCurrentVoxel(const int index);
        void updateCurrentVoxel();
        const glm::vec3 getVoxelPosition() const;
        const glm::vec3 getVoxelScale() const;
        
    protected:
        void register_(const std::string &name);
        void unregister_(const std::string &name);
        void animateVoxels();
        void updateColors();

        int lReg;
        std::vector<glm::mat4> sidesMatrix;
        glm::ivec4 numNodes;
        ofxVecExpr<glm::vec4> lNumNodes;
        ofxVecExpr<glm::vec3> lNodeSize;
        ofxVecExpr<glm::vec3> lNodeSpacing;
        ofxVecExpr<glm::vec3> lNodeDisplacement;
        ofxVecExpr<glm::vec3> lNodeRotation;
        std::vector<glm::vec3> explicitNodeDisplacement;
        float noiseMult = 0;
        glm::vec3 noiseOffset;
        std::shared_ptr<ofxColorTheory::ColorWheelScheme> scheme;
        
        ofParameter<int> pColorScheme;
        ofParameter<int> pNumColors;
        ofParameter<float> pNoise;
        ofxVecExpr<glm::vec3> pNoiseOffset;
        
        float posX, posY, posZ, curIdx;
        
        std::shared_ptr<Voxel> currentVoxel;
        
        static std::map<std::string, Symbol*> symbols;
        
    };
    
}
