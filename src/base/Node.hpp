#pragma once

#include "ofMatrix4x4.h"
#include <glm/gtc/quaternion.hpp>

namespace vxls {
    
    class Node {
        
    public:
        
        const glm::vec3 & getPosition() const {
            return pos;
        }
        void setPosition(const glm::vec3 &value) {
            pos = value;
        }
        const glm::vec3 & getRotation() const {
            return rotation;
        }
        void setRotation(const glm::vec3 &rot) {
            rotation = rot;
        }
        const glm::quat &getOrientation() const {
            return orientation;
        }
        void setOrientation(const glm::quat &orient) {
            orientation = orient;
        }
        const glm::vec3 &getScale() {
            return scale;
        }
        void setScale(const glm::vec3 &s) {
            scale = s;
        }
        const glm::mat4 &getLocalTransformMatrix() const {
            return localTransformMatrix;
        }
        virtual void update(const glm::mat4 &mat);
        
    protected:
        glm::vec3 pos;
        glm::vec3 rotation;
        glm::quat orientation;
        glm::vec3 scale = glm::vec3(1.f);
        glm::mat4 localTransformMatrix;
        
    };
    
}
