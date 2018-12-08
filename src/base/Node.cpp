#include "Node.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

using namespace vxls;

void Node::update(const glm::mat4 &mat) {
    ofQuaternion orient;
    orient.makeRotate(rotation.x, ofVec3f(1.0, 0.0, 0.0), rotation.y, ofVec3f(0.0, 1.0, 0.0), rotation.z, ofVec3f(0.0, 0.0, 1.0));
    orientation = glm::quat(orient);
    localTransformMatrix = glm::translate(glm::mat4(1.0), pos);
    localTransformMatrix = localTransformMatrix * glm::toMat4((const glm::quat&)orientation);
    localTransformMatrix = glm::scale(localTransformMatrix, scale);
}
