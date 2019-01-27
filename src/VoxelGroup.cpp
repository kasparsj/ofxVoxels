#include "VoxelGroup.hpp"
#include "Strings.hpp"

using namespace vxls;

const std::map<int,std::string> VoxelGroup::REG_POINTS = createRegPoints();
const std::vector<glm::vec3> VoxelGroup::REG = createReg();
const std::vector<glm::mat4> VoxelGroup::ROT = createRot();

void VoxelGroup::setupParameterGroup() {
    pGroup.add(pPos.set(Strings::POSITION, glm::vec3(0)).setSliderMinMax(glm::vec3(-10000), glm::vec3(10000)));
    pGroup.add(pRotation.set(Strings::ROTATION, glm::vec3(0), glm::vec3(0), glm::vec3(360.f)));
    pGroup.add(pReg.set(Strings::REGISTRATION, pReg.get(), (int)Registration::CENTER, (int)Registration::BACK));
    pGroup.add(pSide.set(Strings::PARENT_SIDE, pSide.get(), (int)Registration::CENTER, (int)Registration::BACK));
    pGroup.add(pNumNodes.set(Strings::NODES, glm::ivec4(10, 10, 10, 1), glm::ivec4(1), glm::ivec4(100)).setSliderMinMax(glm::ivec4(1), glm::ivec4(30)));
    pGroup.add(pNodeSize.set(Strings::NODE_SIZE, glm::vec3(20), glm::vec3(1), glm::vec3(1000)).setSliderMinMax(glm::vec3(1), glm::vec3(400)));
    pGroup.add(pNodeSpacing.set(Strings::NODE_SPACING, glm::vec3(20), glm::vec3(-400), glm::vec3(400)));
    pGroup.add(pNodeDisplacement.set(Strings::NODE_DISPLACEMENT, glm::vec3(0), glm::vec3(0), glm::vec3(1000)).setSliderMinMax(glm::vec3(0), glm::vec3(100)));
    pGroup.add(pNodeRotation.set(Strings::NODE_ROTATION, glm::vec3(0), glm::vec3(0), glm::vec3(360.f)));

}

void VoxelGroup::clear() {
    voxels.clear();
}

void VoxelGroup::update(const glm::mat4 &mat) {
    BaseObject::update(mat);
    for (int i=0; i<voxels.size(); i++) {
        const std::shared_ptr<Voxel> &voxel = voxels[i];
        updateVoxel(i);
        voxel->update(mat * localTransformMatrix);
        matrices[i] = mat * localTransformMatrix * voxel->getLocalTransformMatrix();
        colors[i] = voxel->getColor();
    }
}

void VoxelGroup::updateVoxel(const int i) {
    if (voxelRotation.size() > i) {
        const std::shared_ptr<Voxel> &voxel = voxels[i];
        voxel->setRotation(voxelRotation[i]);
    }
}
