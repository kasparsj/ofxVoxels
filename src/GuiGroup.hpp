#pragma once

#include "ofxGuiGroup.h"
#include "ofxExpr.hpp"
#include "ofxVecExpr.hpp"
#include "ofxExprInputField.hpp"
#include "ofxVecExprInputField.hpp"

namespace vxls {
    
    class GuiGroup : public ofxGuiGroup {
        
    public:
        GuiGroup();
        GuiGroup(const ofParameterGroup & parameters, const std::string& _filename = "settings.xml", float x = 10, float y = 10);
        GuiGroup * setup(const ofParameterGroup & parameters, const std::string& filename = "settings.xml", float x = 10, float y = 10);
        
        using ofxGuiGroup::add;
        void add(const ofxExpr &parameter) {
            add(new ofxExprInputField(parameter, b.width));
        }
        void add(const ofxVecExpr<glm::vec2> &parameter) {
            add(new ofxVecExprInputField<glm::vec2>(parameter, b.width));
        }
        void add(const ofxVecExpr<glm::vec3> &parameter) {
            add(new ofxVecExprInputField<glm::vec3>(parameter, b.width));
        }
        void add(const ofxVecExpr<glm::vec4> &parameter) {
            add(new ofxVecExprInputField<glm::vec4>(parameter, b.width));
        }
        
    };
    
}
