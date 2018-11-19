#include "Animations.hpp"
#include "ofMain.h"
#include "ofxEasing.h"

using namespace vxls;

const std::map<int, std::string> Animations::LABELS = createLabels();
float Animations::duration = 5.f;

void Animations::rotate(glm::quat & orientation, glm::vec3 &rotationSpeed) {
    ofQuaternion orient;
    orient.makeRotate(rotationSpeed.x, ofVec3f(1.0, 0.0, 0.0), rotationSpeed.y, ofVec3f(0.0, 1.0, 0.0), rotationSpeed.z, ofVec3f(0.0, 0.0, 1.0));
    orientation = orientation * glm::quat(orient);
}

void Animations::threesixty(glm::quat & orientation, glm::vec3 &rotationSpeed, float startRotation) {
    ofQuaternion orient;
    orient.makeRotate(ease(startRotation, startRotation+360.f, ofxeasing::elastic::easeInOut), rotationSpeed.x, rotationSpeed.y, rotationSpeed.z);
    orientation = glm::quat(orient);
}

template<typename Function>
float Animations::ease(float minOut, float maxOut, Function easing) {
    float time = ofGetElapsedTimef();
    return ofxeasing::map(fmod(time, duration), 0, duration, minOut, maxOut, easing);
}
