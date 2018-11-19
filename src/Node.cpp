#include "Node.hpp"
#include "ofVectorMath.h"

using namespace vxls;

void Node::update(const glm::mat4 &mat) {
    switch ((Animation)pAnim.get()) {
        case Animation::rotate:
            Animations::rotate(orientation, rotationSpeed);
            break;
        case Animation::threesixty:
            Animations::threesixty(orientation, rotationSpeed, rotation);
            break;
    }
    localTransformMatrix = glm::translate(glm::mat4(1.0), toGlm(pPos.get()));
    localTransformMatrix = localTransformMatrix * glm::toMat4((const glm::quat&)orientation);
    localTransformMatrix = glm::scale(localTransformMatrix, toGlm(scale));
}
