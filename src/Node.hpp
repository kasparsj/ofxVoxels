#pragma once

#include "Animations.hpp"
#include "ofMath.h"
#include "ofMatrix4x4.h"
#include "ofColor.h"
#include "ofParameter.h"

namespace vxls {
    
    class Node {
        
    public:
        
        const glm::vec3 & getPosition() {
            return pos;
        }
        void setPosition(const glm::vec3 &value) {
            pos = value;
        }
        const glm::quat &getOrientation() {
            return orientation;
        }
        void setOrientation(const glm::quat &q) {
            orientation = q;
        }
        const glm::vec3 &getScale() {
            return scale;
        }
        void setScale(const glm::vec3 &s) {
            scale = s;
        }
        const glm::mat4 &getLocalTransformMatrix() {
            return localTransformMatrix;
        }
        const float getRotation() {
            return rotation;
        }
        const glm::vec3 & getRotationSpeed() {
            return rotationSpeed;
        }
        void setRotation(const glm::vec3 &maxSpeed, float rotation = 0.f) {
            this->rotation = rotation;
            this->rotationSpeed.x = maxSpeed.x - ofRandom(maxSpeed.x*2.f);
            this->rotationSpeed.y = maxSpeed.y - ofRandom(maxSpeed.y*2.f);
            this->rotationSpeed.z = maxSpeed.z - ofRandom(maxSpeed.z*2.f);
        }
        const Animation getAnimation() {
            return (Animation)pAnim.get();
        }
        void setAnimation(Animation value) {
            pAnim.set((int)value);
        }
        const ofColor &getColor() {
            return pColor.get();
        }
        virtual void setColor(ofColor color) {
            pColor.set(color);
        }
        virtual void randomize() { }
        virtual void randomizeColor() {
            setColor(ofFloatColor(ofRandom(1.f), ofRandom(1.f), ofRandom(1.f)));
        }
        virtual void update(const glm::mat4 &mat);
        virtual const std::vector<ofMatrix4x4> & getMatrices() { }
        virtual const std::vector<ofFloatColor> & getColors() { }
        
    protected:
        glm::vec3 pos;
        glm::quat orientation;
        glm::vec3 scale = glm::vec3(1.f);
        glm::mat4 localTransformMatrix;
        float rotation = 0.f;
        glm::vec3 rotationSpeed;
        ofParameter<int> pAnim = 0;
        ofParameter<ofColor> pColor;
        
    };
    
}
