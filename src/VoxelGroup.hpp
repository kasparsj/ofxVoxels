#pragma once

#include "BaseObject.hpp"
#include "HasGui.hpp"
#include "HasColor.hpp"
#include "Voxel.hpp"

namespace vxls {
    
    enum class Registration { CENTER = 0, TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4, FRONT = 5, BACK = 6 };
    
    class VoxelGroup : public BaseObject, public HasGui, public HasColor {
        
    public:
        static const std::map<int,std::string> REG_POINTS;
        static std::map<int,std::string> createRegPoints() {
            std::map<int,std::string> regPoints;
            regPoints[(int)Registration::CENTER] = "center";
            regPoints[(int)Registration::TOP] = "top";
            regPoints[(int)Registration::BOTTOM] = "bottom";
            regPoints[(int)Registration::LEFT] = "left";
            regPoints[(int)Registration::RIGHT] = "right";
            regPoints[(int)Registration::FRONT] = "front";
            regPoints[(int)Registration::BACK] = "back";
            return regPoints;
        }
        static std::vector<glm::vec3> createReg() {
            std::vector<glm::vec3> v;
            v.push_back(glm::vec3(0));
            v.push_back(glm::vec3(0, -0.5, 0));
            v.push_back(glm::vec3(0, 0.5, 0));
            v.push_back(glm::vec3(-0.5, 0, 0));
            v.push_back(glm::vec3(0.5, 0, 0));
            v.push_back(glm::vec3(0, 0, 0.5));
            v.push_back(glm::vec3(0, 0, -0.5));
            return v;
        };
        static std::vector<glm::mat4> createRot() {
            std::vector<glm::mat4> v;
            v.push_back(glm::mat4());
            v.push_back(glm::mat4());
            v.push_back(glm::mat4());
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(0, 1.f, 0)));
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(0, -1.f, 0)));
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(1.f, 0, 0)));
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(-1.f, 0, 0)));
            return v;
        }
        static const std::vector<glm::vec3> REG;
        static const std::vector<glm::mat4> ROT;
        
        virtual void update(const glm::mat4& mat);
        virtual void updateVoxel(const int i);
        const std::vector<ofMatrix4x4> & getMatrices() {
            return matrices;
        }
        const std::vector<ofFloatColor> & getColors() {
            return colors;
        }
        virtual void clear();
        
        void resizeVoxels(int size) {
            if (size < voxels.size()) {
                clear();
            }
            for (int i=voxels.size(); i<size; i++) {
                addVoxel();
            }
        }
        
        const std::shared_ptr<Voxel> &addVoxel() {
            std::shared_ptr<Voxel> voxel(new Voxel);
            voxels.push_back(voxel);
            return voxels[voxels.size()-1];
        }
        
        const std::shared_ptr<Voxel> &getVoxel(int index) {
            return voxels[index];
        }
        
        virtual int countVoxels() const {
            return voxels.size();
        }

        const Registration getRegistration() const {
            return (Registration) pReg.get();
        }
        const Registration getSide() const {
            return (Registration) pSide.get();
        }
        ofParameter<int> & getRegistrationParam() {
            return pReg;
        }
        ofParameter<int> & getSideParam() {
            return pSide;
        }
        ofxVecExpr<glm::vec4> &getNumNodesExpr() {
            return pNumNodes;
        }
        ofxVecExpr<glm::vec3> & getNodeSizeExpr() {
            return pNodeSize;
        }
        ofxVecExpr<glm::vec3> & getNodeSpacingExpr() {
            return pNodeSpacing;
        }
        ofxVecExpr<glm::vec3> & getNodeDisplacementExpr() {
            return pNodeDisplacement;
        }
        ofxVecExpr<glm::vec3> & getNodeRotationExpr() {
            return pNodeRotation;
        }
        virtual void setupParameterGroup();
        
    protected:
        std::vector<std::shared_ptr<Voxel>> voxels;
        std::vector<ofMatrix4x4> matrices;
        std::vector<ofFloatColor> colors;
        ofParameter<int> pReg = 0;
        ofParameter<int> pSide = 0;
        glm::vec3 dims;
        glm::vec3 origin;
        ofxVecExpr<glm::vec4> pNumNodes;
        ofxVecExpr<glm::vec3> pNodeSize;
        ofxVecExpr<glm::vec3> pNodeSpacing;
        ofxVecExpr<glm::vec3> pNodeDisplacement;
        ofxVecExpr<glm::vec3> pNodeRotation;
        std::vector<glm::vec3> voxelRotation;
        
    };
    
}
