#include "Symbol.hpp"
#include "Strings.hpp"

using namespace vxls;

ofEvent<std::string> Symbol::added;
ofEvent<std::string> Symbol::removed;
std::map<std::string, Symbol*> Symbol::symbols;

Symbol* Symbol::find(const std::string &name) {
    std::map<std::string,Symbol*>::iterator it = symbols.find(name);
    return it != symbols.end() ? it->second : 0;
}

void Symbol::register_(const std::string &name) {
    symbols[name] = this;
    std::string value = name;
    ofNotifyEvent(added, value);
}

void Symbol::unregister_(const std::string &name) {
    std::string value = name;
    ofNotifyEvent(removed, value);
    symbols.erase(name);
}

Symbol::Symbol() {
    lPos.setName("lPos");
    lNumNodes.setName("lNumNodes");
    lNodeSize.setName("lNodeSize");
    lNodeSpacing.setName("lNodeSpacing");
    lNodeDisplacement.setName("lNodeDisplacement");
    lNodeRotation.setName("lNodeRotation");
    ofxVecExpr<glm::vec3>* lNodeProps[4] = {&lNodeSize, &lNodeSpacing, &lNodeDisplacement, &lNodeRotation};
    for (int i=0; i<4; i++) {
        lNodeProps[i]->addVar("x", posX, false);
        lNodeProps[i]->addVar("y", posY, false);
        lNodeProps[i]->addVar("z", posZ, false);
    }
    ofxVecExpr<glm::vec3>* pNodeProps[4] = {&pNodeSize, &pNodeSpacing, &pNodeDisplacement, &pNodeRotation};
    for (int i=0; i<4; i++) {
        pNodeProps[i]->addVar("x", posX, false);
        pNodeProps[i]->addVar("y", posY, false);
        pNodeProps[i]->addVar("z", posZ, false);
    }
}

void Symbol::resize() {
    lNumNodes = pNumNodes;
    numNodes = (glm::ivec4) lNumNodes.get();
    const int count = countVoxels();
    VoxelGroup::resizeVoxels(count);
    if (children.size() == 0) {
        matrices.clear();
        matrices.resize(count);
        colors.clear();
        colors.resize(count);
    }
}

void Symbol::transform() {
    lReg = pReg.get();
    lNodeSize = pNodeSize;
    lNodeSpacing = pNodeSpacing;
    lNodeDisplacement = pNodeDisplacement;
    lNodeRotation = pNodeRotation;
    
    const int count = countVoxels();
    const bool explicitDisplacement = lNodeDisplacement.isExplicit();
    voxelRotation.clear();
    voxelRotation.resize(count);
    explicitNodeDisplacement.clear();
    explicitNodeDisplacement.resize(count);
    for (int i=0; i<count; i++) {
        voxelRotation[i] = lNodeRotation.get();
        if (explicitDisplacement) {
            explicitNodeDisplacement[i] = ofRandom(lNodeDisplacement.getExplicit());
        }
    }
    
    updateDims();
    animate();
}

void Symbol::animate() {
    const int count = countVoxels();
    for (int i=0; i<count; i++) {
        setCurrentVoxel(i);
        updateCurrentVoxel();
    }
}

void Symbol::setCurrentVoxel(const int index)  {
    currentVoxel = voxels[index];
    const glm::ivec3 &idx3 = unpack(index);
    const glm::vec3 posNorm = posNormal(idx3);
    curIdx = index;
    posX = posNorm.x;
    posY = posNorm.y;
    posZ = posNorm.z;
}

void Symbol::updateCurrentVoxel() {
    currentVoxel->setPosition(getVoxelPosition());
    currentVoxel->setScale(getVoxelScale());
}

const glm::vec3 Symbol::getVoxelPosition() const {
    const glm::vec3 &nodeSpacing = lNodeSpacing.get();
    const glm::vec3 &nodeDisplacement = explicitNodeDisplacement[curIdx] + lNodeDisplacement.getNonExplicit();
    const glm::vec3 &nodeSize = lNodeSize.get();
    float nodeX = posX * (nodeSize.x + nodeSpacing.x);
    float nodeY = posY * (nodeSize.y + nodeSpacing.y);
    float nodeZ = posZ * (nodeSize.z + nodeSpacing.z);
    return origin + glm::vec3(nodeX, nodeY, nodeZ) + nodeDisplacement;
}

const glm::vec3 Symbol::getVoxelScale() const {
    return lNodeSize.get();
}

void Symbol::setupParameterGroup() {
    VoxelGroup::setupParameterGroup();
    pGroup.add(pColor.set(Strings::NODE_COLOR, ofColor::magenta));
    pGroup.add(pColorScheme.set(Strings::NODE_COLOR_SCHEME, 0, 0, (ofxColorTheory::ColorWheelSchemes::SCHEMES.size() - 1)));
    pGroup.add(pNumColors.set("NumNodeColors", 256, 1, 1000));
    pGroup.add(pNoise.set("NodeNoiseMult", 0.1, 0.001, 0.2));
    pGroup.add(pNoiseOffset.set("NodeNoiseOffset", glm::vec3(0.1)).setSliderMinMax(glm::vec3(0), glm::vec3(0.5)));
}

void Symbol::setColors(const std::vector<ofColor> & colors) {
    for (int i=0; i<voxels.size(); i++) {
        float n = noise(posNormal(unpack(i)));
        voxels[i]->setColor(colors[n * colors.size()]);
    }
}

void Symbol::update(const glm::mat4 &mat) {
    updateFromParams();
    Container::update(mat);
}

void Symbol::updateFromParams() {
    if (pGroup.size() > 0) {
        BaseObject::updateFromParams();
        if (lNumNodes != pNumNodes) {
            resize();
            transform();
            updateColors();
        }
        else {
            if (isTransformDirty()) {
                transform();
            }
            else if (isTransformAnim()) {
                animate();
            }
            if (lNodeRotation.isTimeDependent()) {
                animateVoxels();
            }
            updateColors();
        }
        //boxes.write(BOXES_RES, colors);
    }
}

void Symbol::animateVoxels() {
    const int count = countVoxels();
    const std::shared_ptr<ofxExpr> &x = lNodeRotation[0];
    const std::shared_ptr<ofxExpr> &y = lNodeRotation[1];
    const std::shared_ptr<ofxExpr> &z = lNodeRotation[2];
    const bool animX = x->isTimeDependent();
    const bool animY = y->isTimeDependent();
    const bool animZ = z->isTimeDependent();
    for (int i=0; i<count; i++) {
        setCurrentVoxel(i);
        if (animX) {
            voxelRotation[i].x = x->get();
        }
        if (animY) {
            voxelRotation[i].y = y->get();
        }
        if (animZ) {
            voxelRotation[i].z = z->get();
        }
    }
}

void Symbol::updateColors() {
    float mult = pNoise.get();
    noiseMult = mult;
    noiseOffset = pNoiseOffset.get();
    std::vector<ofColor> colors;
    if (pNumColors.get() > 1) {
        scheme = ofxColorTheory::ColorWheelSchemes::SCHEMES[pColorScheme.get()];
        scheme->setPrimaryColor(pColor.get());
        colors = scheme->interpolate(pNumColors.get());
    }
    else {
        colors.push_back(pColor.get());
    }
    setColors(colors);
}

void Symbol::updateDims() {
    const glm::vec3 nodes = (glm::vec3(numNodes) * lNodeSize.get());
    const glm::vec3 spaces = (glm::vec3(numNodes) - glm::vec3(1.f)) * lNodeSpacing.get();
    dims = (nodes + spaces);
    origin = (VoxelGroup::REG[(int) pReg.get()] * dims);
    int l = (int) Registration::BACK;
    std::vector<float> distances;
    distances.push_back(0);
    distances.push_back(dims.y / 2.f);
    distances.push_back(dims.y / 2.f);
    distances.push_back(dims.x / 2.f);
    distances.push_back(dims.x / 2.f);
    distances.push_back(dims.z / 2.f);
    distances.push_back(dims.z / 2.f);
    sidesMatrix.resize(l+1);
    for (int side=0; side<=l; side++) {
        sidesMatrix[side] = glm::translate(glm::mat4(1.0), toGlm(glm::vec3(0, distances[side], 0)));
        sidesMatrix[side] *= ROT[side];
    }
}

void Symbol::randomize() {
    const glm::vec4 &min = pNumNodes.getMin();
    const glm::vec4 &max = pNumNodes.getMax();
    pNumNodes.set(glm::vec4(ofRandom(min.x, max.x), ofRandom(min.y, max.y), ofRandom(min.z, max.z), 1));
    pNoise.setRandom();
    pNoiseOffset.setRandom();
    pNodeSize.setRandom();
    pNodeSpacing.setRandom();
    if (pNodeDisplacement.isExplicit()) {
        pNodeDisplacement.setRandom();
    }
}

void Symbol::randomizeColor() {
    HasColor::randomizeColor();
    pColorScheme.setRandom();
    //pNumColors.setRandom();
}
