#include "Camera.hpp"
#include "Strings.hpp"

using namespace vxls;

Camera::Camera() {
    ofAddListener(Symbol::added, this, &Camera::onSymbolAdded);
    ofAddListener(Symbol::removed, this, &Camera::onSymbolRemoved);
}

void Camera::onSymbolAdded(std::string &name) {
    
}

void Camera::onSymbolRemoved(std::string &name) {
    if (sLookAt == Symbol::find(name)) {
        sLookAt = NULL;
    }
}

void Camera::setupParameterGroup() {
    pGroup.setName("Camera");
    pGroup.add(pPos.set(Strings::POSITION, glm::vec3(0)).setSliderMinMax(glm::vec3(-10000), glm::vec3(10000)));
    pGroup.add(pRotation.set(Strings::ROTATION, glm::vec3(0), glm::vec3(0), glm::vec3(360.f)));
    pGroup.add(pLookAt.set(Strings::LOOK_AT));
    
//    camGroup.add(camOrbit.set("Orbit", false));
//    camGroup.add(camAnim.set("Animate", false));
//    camGroup.add(animDur.set("AnimDuration", 2.f, 1.f, 20.f));
//    camGroup.add(camAnimY.set("AnimY", false));
//    camGroup.add(camAngle.set("Angle", 0, 0, 360));
//    camGroup.add(camDist.set("Distance", 500, 0, 7000));
//    camGroup.add(camY.set("Y", 200, -1000, 2000));
    
//    if (camOrbit.get() == 1) {
//        cam.setPosition(normalize(glm::vec3(cos(ofGetElapsedTimef() * 1), 1.5f, sin(ofGetElapsedTimef() * 1))) * 1600.f);
//        cam.lookAt(glm::vec3(0, 0, 0));
//    }
//    else if (camAnim.get() == 1) {
//        //camAngle.set(vxls::Animations::ease(0, 2*PI, ofxeasing::exp::easeInOut));
//        if (!animHalf && camAngle.get() >= PI) {
//            animHalf = true;
//            randomize();
//        }
//        else if (camAngle.get() < PI) {
//            animHalf = false;
//        }
//        cam.setPosition(ofVec3f(camDist.get() * sin(camAngle), camY.get() * (camAnimY == 1 ? cos(camAngle) : 1.f), camDist.get() * cos(camAngle)));
//        cam.lookAt(ofVec3f(0, 0, 0));
//    }
}

void Camera::updateFromParams() {
    BaseObject::updateFromParams();
    if (pLookAt.get() != lLookAt) {
        lLookAt = pLookAt.get();
        Symbol *newLookAt = Symbol::find(lLookAt);
        if (newLookAt != 0) {
            sLookAt = newLookAt;
        }
    }
    if (sLookAt != 0) {
        lookAt = sLookAt->getPosition();
    }
    else {
        lookAt = glm::vec3(0);
    }
}
