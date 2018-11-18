#include "Object.hpp"
#include "Strings.hpp"

using namespace ofxVoxels;

const map<int,string> Object::REG_POINTS = createRegPoints();
const vector<glm::vec3> Object::REG = createReg();
const vector<glm::mat4> Object::ROT = createRot();

void Object::setupParameterGroup() {
    pGroup.add(pPos.set(Strings::POSITION, glm::vec3(0)).setSliderMinMax(glm::vec3(-10000), glm::vec3(10000)));
    pGroup.add(pAnim.set(Strings::ANIMATION, (int)Animation::none, (int)Animation::none, (int)Animation::threesixty));
    pGroup.add(pReg.set(Strings::REGISTRATION, pReg.get(), (int)Registration::CENTER, (int)Registration::BACK));
    pGroup.add(pSide.set(Strings::PARENT_SIDE, pSide.get(), (int)Registration::CENTER, (int)Registration::BACK));
    pGroup.add(pNumNodes.set(Strings::NODES, glm::ivec4(10, 10, 10, 1), glm::ivec4(1), glm::ivec4(100)).setSliderMinMax(glm::ivec4(1), glm::ivec4(30)));
    pGroup.add(pNodeSize.set(Strings::NODE_SIZE, glm::vec3(20), glm::vec3(1), glm::vec3(1000)).setSliderMinMax(glm::vec3(1), glm::vec3(400)));
    pGroup.add(pNodeSpacing.set(Strings::NODE_SPACING, glm::vec3(20), glm::vec3(-400), glm::vec3(400)));
    pGroup.add(pNodeDisplacement.set(Strings::NODE_DISPLACEMENT, glm::vec3(0), glm::vec3(0), glm::vec3(1000)).setSliderMinMax(glm::vec3(0), glm::vec3(100)));
    pGroup.add(pNodeAnim.set(Strings::NODE_ANIM, (int)Animation::none, (int)Animation::none, (int)Animation::threesixty));

}

void Object::clear() {
    nodes.clear();
}

void Object::update(const glm::mat4 &mat) {
    Node::update(mat);
    for (int i=0; i<nodes.size(); i++) {
        const shared_ptr<Node> &node = nodes[i];
        node->setAnimation((Animation)pNodeAnim.get());
        node->update(mat * localTransformMatrix);
        matrices[i] = mat * localTransformMatrix * node->getLocalTransformMatrix();
        colors[i] = node->getColor();
    }
}
