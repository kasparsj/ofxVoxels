#pragma once

#include "Node.hpp"
#include "ofxExpr.hpp"
#include "ofxVecExpr.hpp"
#include "GuiGroup.hpp"

namespace vxls {
    
    enum class Registration { CENTER = 0, TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4, FRONT = 5, BACK = 6 };
    
    class Object : public Node {
        
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
        const std::vector<ofMatrix4x4> & getMatrices() {
            return matrices;
        }
        const std::vector<ofFloatColor> & getColors() {
            return colors;
        }
        virtual void clear();
        
        void resizeNodes(int size) {
            if (size < nodes.size()) {
                clear();
            }
            for (int i=nodes.size(); i<size; i++) {
                addNode();
            }
        }
        
        const std::shared_ptr<Node> &addNode() {
            std::shared_ptr<Node> node(new Node);
            nodes.push_back(node);
            return nodes[nodes.size()-1];
        }
        
        const std::shared_ptr<Node> &getNode(int index) {
            return nodes[index];
        }
        
        int countNodes() {
            return nodes.size();
        }

        void setPosition(const glm::vec3 &value) {
            pPos.set(value);
        }
        const Registration getRegistration() const {
            return (Registration) pReg.get();
        }
        void setRegistration(Registration value) {
            pReg.set((int)value);
        }
        const Registration getSide() const {
            return (Registration) pSide.get();
        }
        void setSide(Registration value) {
            pSide.set((int) value);
        }
        const Animation getNodeAnimation() const {
            return (Animation) pNodeAnim.get();
        }
        const ofxVecExpr<glm::vec4> &getNumNodes() const {
            return pNumNodes;
        }
        void setNumNodes(const glm::vec4 &value) {
            pNumNodes.set(value);
        }
        void setNodeAnimation(Animation value) {
            pNodeAnim.set((int)value);
        }
        const ofxVecExpr<glm::vec3> & getNodeSize() const {
            return pNodeSize;
        }
        void setNodeSize(const glm::vec3 & value) {
            pNodeSize.set(value);
        }
        const ofxVecExpr<glm::vec3> & getNodeSpacing() const {
            return pNodeSpacing;
        }
        void setNodeSpacing(const glm::vec3 &value) {
            pNodeSpacing.set(value);
        }
        const ofxVecExpr<glm::vec3> & getNodeDisplacement() const {
            return pNodeDisplacement;
        }
        void setNodeDisplacement(const glm::vec3 &value) {
            pNodeDisplacement.set(value);
        }
        ofParameterGroup & getParameterGroup() {
            if (pGroup.size() == 0) {
                setupParameterGroup();
            }
            return pGroup;
        }
        std::shared_ptr<GuiGroup> & getGuiGroup() {
            if (guiGroup.get() == NULL) {
                guiGroup = std::shared_ptr<GuiGroup>(new GuiGroup(getParameterGroup()));
            }
            return guiGroup;
        }
        virtual void setupParameterGroup();
        
    protected:
        ofxVecExpr<glm::vec3> pPos;
        std::vector<std::shared_ptr<Node>> nodes;
        std::vector<ofMatrix4x4> matrices;
        std::vector<ofFloatColor> colors;
        ofParameter<int> pReg = 0;
        ofParameter<int> pSide = 0;
        glm::vec3 dims;
        glm::vec3 origin;
        std::shared_ptr<GuiGroup> guiGroup;
        ofParameterGroup pGroup;
        ofxVecExpr<glm::vec4> pNumNodes;
        ofParameter<int> pNodeAnim;
        ofxVecExpr<glm::vec3> pNodeSize;
        ofxVecExpr<glm::vec3> pNodeSpacing;
        ofxVecExpr<glm::vec3> pNodeDisplacement;
        
    };
    
}
