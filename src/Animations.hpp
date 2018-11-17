#pragma once

#include "ofMain.h"

namespace ofxVoxels {
    
    using namespace std;

    enum class Animation { none = 0, rotate = 1, threesixty = 2 };
    
    class Animations {
        
    public:
        static const map<int, string> LABELS;
        static map<int, string> createLabels() {
            map<int, string> labels;
            labels[(int)Animation::none] = "none";
            labels[(int)Animation::rotate] = "rotate";
            labels[(int)Animation::threesixty] = "threesixty";
            return labels;
        }
        
        static void rotate(glm::quat &orientation, glm::vec3 &rotationSpeed);
        static void threesixty(glm::quat &orientation, glm::vec3 &rotationSpeed, float startRotation = 0.f);
        
        template<typename Function>
        static float ease(float minOut, float maxOut, Function easing);
        
        static float duration;
        
    };
    
}
