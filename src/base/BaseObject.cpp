#include "BaseObject.hpp"

using namespace vxls;

void BaseObject::update(const glm::mat4 &mat) {
    updateFromParams();
    Node::update(mat);
}

void BaseObject::updateFromParams() {
    if (lPos != pPos) {
        lPos = pPos;
        pos = lPos.get();
    }
    else if (lPos.hasExprSymbol("t")) {
        pos = lPos.get();
    }
    if (lRotation != pRotation) {
        lRotation = pRotation;
        rotation = lRotation.get();
    }
    else if (lRotation.hasExprSymbol("t")) {
        rotation = lRotation.get();
    }
}
