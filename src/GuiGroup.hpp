#pragma once

#include "ofxGuiGroup.h"
#include "ofxExpr.hpp"
#include "ofxVecExpr.hpp"
#include "ofxExprInputField.hpp"
#include "ofxVecExprInputField.hpp"

namespace ofxVoxels {
    
    using namespace std;

    class GuiGroup : public ofxGuiGroup {
        
    public:
        GuiGroup();
        GuiGroup(const ofParameterGroup & parameters, const std::string& _filename = "settings.xml", float x = 10, float y = 10);
        GuiGroup * setup(const ofParameterGroup & parameters, const std::string& filename = "settings.xml", float x = 10, float y = 10);
        
        template<class Type>
        void add(const ofxExpr<Type> &parameter) {
            ofxGuiGroup::add(new ofxExprInputField<Type>(parameter, b.width));
        }
        
        template<class Type>
        void add(const ofxVecExpr<Type> &parameter) {
            ofxGuiGroup::add(new ofxVecExprInputField<Type>(parameter, b.width));
        }
        
    };
    
}
