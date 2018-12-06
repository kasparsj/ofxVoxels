#include "Node.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

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
    localTransformMatrix = glm::translate(glm::mat4(1.0), pos);
    localTransformMatrix = localTransformMatrix * glm::toMat4((const glm::quat&)orientation);
    localTransformMatrix = glm::scale(localTransformMatrix, scale);
}
