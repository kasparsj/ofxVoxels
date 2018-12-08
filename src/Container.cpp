#include "Container.hpp"

using namespace vxls;

void Container::clear() {
    VoxelGroup::clear();
    children.clear();
}

void Container::update(const glm::mat4 &mat) {
    if (children.size() > 0) {
        Node::update(mat);
        matrices.clear();
        colors.clear();
        for (int i=0; i<voxels.size(); i++) {
            const std::shared_ptr<Voxel> &voxel = voxels[i];
            updateVoxel(i);
            voxel->update(mat * localTransformMatrix);
            matrices.push_back(mat * localTransformMatrix * voxel->getLocalTransformMatrix());
            colors.push_back(voxel->getColor());
        }
        for (int i=0; i<children.size(); i++) {
            const std::shared_ptr<Container> &child = children[i];
            const glm::mat4 &childMatrix = getChildMatrix(child);
            child->update(mat * localTransformMatrix * childMatrix);
            const std::vector<ofMatrix4x4> &obj_mat = child->getMatrices();
            const std::vector<ofFloatColor> &obj_col = child->getColors();
            matrices.insert(matrices.begin()+matrices.size(), obj_mat.begin(), obj_mat.end());
            colors.insert(colors.begin()+colors.size(), obj_col.begin(), obj_col.end());
        }
    }
    else {
        VoxelGroup::update(mat);
    }
}
