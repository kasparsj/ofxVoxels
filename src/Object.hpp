#pragma once

#include "Node.hpp"
#include "GuiGroup.hpp"
#include "ofxExpr.hpp"
#include "ofxVecExpr.hpp"

using namespace std;

namespace ofxVoxels {
    
    enum class Registration { CENTER = 0, TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4, FRONT = 5, BACK = 6 };
    
    class Object : public Node {
        
    public:
        static const map<int,string> REG_POINTS;
        static map<int,string> createRegPoints() {
            map<int,string> regPoints;
            regPoints[(int)Registration::CENTER] = "center";
            regPoints[(int)Registration::TOP] = "top";
            regPoints[(int)Registration::BOTTOM] = "bottom";
            regPoints[(int)Registration::LEFT] = "left";
            regPoints[(int)Registration::RIGHT] = "right";
            regPoints[(int)Registration::FRONT] = "front";
            regPoints[(int)Registration::BACK] = "back";
            return regPoints;
        }
        static vector<glm::vec3> createReg() {
            vector<glm::vec3> v;
            v.push_back(glm::vec3(0));
            v.push_back(glm::vec3(0, -0.5, 0));
            v.push_back(glm::vec3(0, 0.5, 0));
            v.push_back(glm::vec3(-0.5, 0, 0));
            v.push_back(glm::vec3(0.5, 0, 0));
            v.push_back(glm::vec3(0, 0, 0.5));
            v.push_back(glm::vec3(0, 0, -0.5));
            return v;
        };
        static vector<glm::mat4> createRot() {
            vector<glm::mat4> v;
            v.push_back(glm::mat4());
            v.push_back(glm::mat4());
            v.push_back(glm::mat4());
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(0, 1.f, 0)));
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(0, -1.f, 0)));
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(1.f, 0, 0)));
            v.push_back(glm::rotate((float)HALF_PI, glm::vec3(-1.f, 0, 0)));
            return v;
        }
        static const vector<glm::vec3> REG;
        static const vector<glm::mat4> ROT;
        
        virtual void update(const glm::mat4& mat);
        const vector<ofMatrix4x4> & getMatrices() {
            return matrices;
        }
        const vector<ofFloatColor> & getColors() {
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
        
        const shared_ptr<Node> &addNode() {
            shared_ptr<Node> node(new Node);
            nodes.push_back(node);
            return nodes[nodes.size()-1];
        }
        
        const shared_ptr<Node> &getNode(int index) {
            return nodes[index];
        }
        
        int countNodes() {
            return nodes.size();
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
        const glm::vec4 &getNumNodes() const {
            return pNumNodes;
        }
        void setNumNodes(const glm::vec4 &value) {
            pNumNodes.set(value);
        }
        void setNodeAnimation(Animation value) {
            pNodeAnim.set((int)value);
        }
        const glm::vec3 & getNodeSize() const {
            return pNodeSize.get();
        }
        void setNodeSize(const glm::vec3 & value) {
            pNodeSize.set(value);
        }
        const glm::vec3 & getNodeSpacing() const {
            return pNodeSpacing.get();
        }
        void setNodeSpacing(const glm::vec3 &value) {
            pNodeSpacing.set(value);
        }
        const glm::vec3 & getNodeDisplacement() const {
            return pNodeDisplacement.get();
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
        shared_ptr<GuiGroup> & getGuiGroup() {
            if (guiGroup.get() == NULL) {
                guiGroup = shared_ptr<GuiGroup>(new GuiGroup(getParameterGroup()));
            }
            return guiGroup;
        }
        virtual void setupParameterGroup();
        
    protected:
        vector<shared_ptr<Node>> nodes;
        vector<ofMatrix4x4> matrices;
        vector<ofFloatColor> colors;
        ofParameter<int> pReg = 0;
        ofParameter<int> pSide = 0;
        glm::vec3 dims;
        glm::vec3 origin;
        shared_ptr<GuiGroup> guiGroup;
        ofParameterGroup pGroup;
        ofParameter<glm::vec4> pNumNodes;
        ofParameter<int> pNodeAnim;
        ofxVecExpr<glm::vec3> pNodeSize;
        ofxVecExpr<glm::vec3> pNodeSpacing;
        ofxVecExpr<glm::vec3> pNodeDisplacement;
        
    };
    
}
