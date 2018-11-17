#include "Container.hpp"

using namespace ofxVoxels;

void Container::clear() {
    Object::clear();
    children.clear();
}

void Container::update(const glm::mat4 &mat) {
    if (children.size() > 0) {
        Node::update(mat);
        matrices.clear();
        colors.clear();
        for (int i=0; i<nodes.size(); i++) {
            const shared_ptr<Node> &node = nodes[i];
            node->setAnimation((Animation)pNodeAnim.get());
            node->update(mat * localTransformMatrix);
            matrices.push_back(mat * localTransformMatrix * node->getLocalTransformMatrix());
            colors.push_back(node->getColor());
        }
        for (int i=0; i<children.size(); i++) {
            const shared_ptr<Container> &child = children[i];
            const glm::mat4 &childMatrix = getChildMatrix(child);
            child->update(mat * localTransformMatrix * childMatrix);
            const vector<ofMatrix4x4> &obj_mat = child->getMatrices();
            const vector<ofFloatColor> &obj_col = child->getColors();
            matrices.insert(matrices.begin()+matrices.size(), obj_mat.begin(), obj_mat.end());
            colors.insert(colors.begin()+colors.size(), obj_col.begin(), obj_col.end());
        }
    }
    else {
        Object::update(mat);
    }
}
