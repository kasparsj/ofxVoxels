#pragma once

#include "ofxGuiGroup.h"

namespace ofxVoxels {
    
    using namespace std;

    class GuiGroup : public ofxGuiGroup {
        
    public:
        GuiGroup();
        GuiGroup(const ofParameterGroup & parameters, const std::string& _filename = "settings.xml", float x = 10, float y = 10);
        GuiGroup * setup(const ofParameterGroup & parameters, const std::string& filename = "settings.xml", float x = 10, float y = 10);
        
    };
    
}
