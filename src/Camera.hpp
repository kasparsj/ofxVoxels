#pragma once

#include "Symbol.hpp"

namespace vxls {
    
    class Camera : public BaseObject, public HasGui {
        
    public:
        Camera();
        void onSymbolAdded(std::string &name);
        void onSymbolRemoved(std::string &removed);
        virtual void setupParameterGroup() override;
        virtual void updateFromParams() override;
        
        const glm::vec3 & getLookAt() const {
            return lookAt;
        }
        void setLookAt(const glm::vec3 &v) {
            lookAt = v;
        }
        
    protected:
        glm::vec3 lookAt;
        ofParameter<std::string> pLookAt;
        std::string lLookAt;
        Symbol *sLookAt = 0;
//        bool animHalf;
        
//        ofParameter<bool> camOrbit;
//        ofParameter<glm::vec3> camOrbitTraj;
//        ofParameter<bool> camAnim;
//        ofParameter<float> animDur;
//        ofParameter<bool> camAnimY;
//        ofParameter<float> camAngle;
//        ofParameter<float> camDist;
//        ofParameter<float> camY;
        
//        void orbitCamera(bool on) {
//            if (on) {
//                camOrbitTraj = cam.getPosition();
//            }
//            camOrbit.set(on);
//            camAnim.set(!on);
//        }
        
    };
    
}
