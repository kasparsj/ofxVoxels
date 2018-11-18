#include "GuiGroup.hpp"
#include "Strings.hpp"
#include "ofxDropdown.h"
#include "Animations.hpp"
#include "Object.hpp"
#include "ColorWheelSchemes.h"

using namespace ofxVoxels;
using namespace ofxColorTheory;

GuiGroup::GuiGroup(const ofParameterGroup & parameters, const std::string& _filename, float x, float y) {
    minimized = false;
    parent = nullptr;
    setup(parameters, filename, x, y);
}

GuiGroup * GuiGroup::setup(const ofParameterGroup & _parameters, const std::string& _filename, float x, float y) {
    b.x = x;
    b.y = y;
    header = defaultHeight;
    spacing = 1;
    spacingNextElement = 3;
    if(parent != nullptr){
        b.width = parent->getWidth();
    }else{
        b.width = defaultWidth;
    }
    clear();
    filename = _filename;
    bGuiActive = false;
    
    for(std::size_t i = 0; i < _parameters.size(); i++){
        string name = _parameters.getName(i);
        if (name == Strings::ANIMATION || name == Strings::NODE_ANIM) {
            auto p = _parameters.get<int>(i);
            ofxGuiGroup::add(new ofxIntDropdown(p, Animations::LABELS, b.width));
        }
        else if (name == Strings::REGISTRATION || name == Strings::PARENT_SIDE) {
            auto p = _parameters.get<int>(i);
            ofxGuiGroup::add(new ofxIntDropdown(p, Object::REG_POINTS, b.width));
        }
        else if (name == Strings::NODE_COLOR_SCHEME) {
            auto p = _parameters.get<int>(i);
            ofxGuiGroup::add(new ofxIntDropdown(p, ColorWheelSchemes::NAMES, b.width));
        }
        else if (name == Strings::NODE_SIZE || name == Strings::NODE_SPACING || name == Strings::NODE_DISPLACEMENT) {
            const ofxVecExpr<glm::vec3>& p = static_cast<const ofxVecExpr<glm::vec3>& >(_parameters.get(i));
            add(p);
        }
        else if (false) {
//            auto p = dynamic_cast<const ofxExpr<float>&>(_parameters.get<float>(i));
//            add(p);
        }
        else {
            string type = _parameters.getType(i);
            if(type == typeid(ofParameter <int32_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <uint32_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <int64_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <uint64_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <int8_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <uint8_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <int16_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <uint16_t> ).name()){
                auto p = _parameters.get<int>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <size_t> ).name()){
                auto p = _parameters.get<size_t>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <float> ).name()){
                auto p = _parameters.getFloat(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <double> ).name()){
                auto p = _parameters.get<double>(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <bool> ).name()){
                auto p = _parameters.getBool(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <void> ).name()){
                auto p = _parameters.getVoid(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <ofDefaultVec2> ).name()){
                auto p = _parameters.getVec2f(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <ofDefaultVec3> ).name()){
                auto p = _parameters.getVec3f(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <ofDefaultVec4> ).name()){
                auto p = _parameters.getVec4f(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <ofColor> ).name()){
                auto p = _parameters.getColor(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <ofShortColor> ).name()){
                auto p = _parameters.getShortColor(i);
                ofxGuiGroup::add(p);
            }else if(type == typeid(ofParameter <ofFloatColor> ).name()){
                auto p = _parameters.getFloatColor(i);
                ofxGuiGroup::add(p);
            }else if(_parameters[i].valueType() == typeid(string).name()){
                if(_parameters[i].isReadOnly()){
                    auto p = _parameters.get(i).castReadOnly<std::string, void>();
                    ofxGuiGroup::add(p);
                }else{
                    auto p = _parameters.getString(i);
                    ofxGuiGroup::add(p);
                }
            }else if(type == typeid(ofParameterGroup).name()){
                auto p = _parameters.getGroup(i);
                ofxGuiGroup * panel = new ofxGuiGroup(p);
                ofxGuiGroup::add(panel);
            }else{
                ofLogWarning() << "ofxBaseGroup; no control for parameter of type " << type;
            }
        }
    }
    
    parameters = _parameters;
    registerMouseEvents();
    
    setNeedsRedraw();
    
    return this;
}
