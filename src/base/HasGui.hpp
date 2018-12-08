#pragma once

#include "GuiGroup.hpp"

namespace vxls {
    
    class HasGui {
        
    public:
        ofParameterGroup & getParameterGroup() {
            if (pGroup.size() == 0) {
                setupParameterGroup();
            }
            return pGroup;
        }
        const std::shared_ptr<GuiGroup> & getGuiGroup() {
            if (guiGroup.get() == NULL) {
                guiGroup = std::shared_ptr<GuiGroup>(new GuiGroup(getParameterGroup()));
            }
            return guiGroup;
        }
        virtual void setupParameterGroup() = 0;
        
    protected:
        std::shared_ptr<GuiGroup> guiGroup;
        ofParameterGroup pGroup;
        
    };
    
}
