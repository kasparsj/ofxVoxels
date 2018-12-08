#pragma once

#include "Node.hpp"
#include "ofxVecExpr.hpp"

namespace vxls {
    
    class BaseObject : public Node {
        
    public:
        ofxVecExpr<glm::vec3> & getPositionExpr() {
            return pPos;
        }
        ofxVecExpr<glm::vec3> & getRotationExpr() {
            return pRotation;
        }
        virtual void update(const glm::mat4 &mat) override;
        virtual void updateFromParams();
        
    protected:
        ofxVecExpr<glm::vec3> pPos;
        ofxVecExpr<glm::vec3> pRotation;
        
        ofxVecExpr<glm::vec3> lPos;
        ofxVecExpr<glm::vec3> lRotation;
        
    };
    
}
