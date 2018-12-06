#include "Struct.hpp"
#include "Strings.hpp"

using namespace vxls;

void Struct::resize() {
    lNumNodes = pNumNodes;
    numNodes = (glm::ivec4) lNumNodes.get();
    const int count = countNodes();
    Object::resizeNodes(count);
    if (children.size() == 0) {
        matrices.clear();
        matrices.resize(count);
        colors.clear();
        colors.resize(count);
    }
}

void Struct::transform() {
    lReg = pReg.get();
    lNodeSize = pNodeSize;
    lNodeSpacing = pNodeSpacing;
    lNodeDisplacement = pNodeDisplacement;
    
    explicitNodeDisplacement.clear();
    const int count = countNodes();
    explicitNodeDisplacement.resize(count);
    if (lNodeDisplacement.isExplicit()) {
        for (int i=0; i<count; i++) {
            explicitNodeDisplacement[i] = ofRandom(lNodeDisplacement.getExplicit());
        }
    }
    
    updateDims();
    animate();
}

void Struct::animate() {
    const int count = countNodes();
    for (int i=0; i<count; i++) {
        setCurrentNode(i);
        updateCurrentNode();
    }
}

void Struct::setCurrentNode(const int index)  {
    currentNode = nodes[index];
    const glm::ivec3 &idx3 = unpack(index);
    const glm::vec3 posNorm = posNormal(idx3);
    curIdx = index;
    posX = posNorm.x;
    posY = posNorm.y;
    posZ = posNorm.z;
}

void Struct::updateCurrentNode() {
    currentNode->setPosition(getNodePosition());
    currentNode->setScale(getNodeScale());
}

const glm::vec3 Struct::getNodePosition() const {
    const glm::vec3 &nodeSpacing = lNodeSpacing.get();
    const glm::vec3 &nodeDisplacement = explicitNodeDisplacement[curIdx] + lNodeDisplacement.getNonExplicit();
    const glm::vec3 &nodeSize = lNodeSize.get();
    float nodeX = posX * (nodeSize.x + nodeSpacing.x);
    float nodeY = posY * (nodeSize.y + nodeSpacing.y);
    float nodeZ = posZ * (nodeSize.z + nodeSpacing.z);
    return origin + glm::vec3(nodeX, nodeY, nodeZ) + nodeDisplacement;
}

const glm::vec3 Struct::getNodeScale() const {
    return lNodeSize.get();
}

void Struct::setupParameterGroup() {
    Object::setupParameterGroup();
    pGroup.add(pColor.set(Strings::NODE_COLOR, ofColor::magenta));
    pGroup.add(pColorScheme.set(Strings::NODE_COLOR_SCHEME, 0, 0, (ofxColorTheory::ColorWheelSchemes::SCHEMES.size() - 1)));
    pGroup.add(pNumColors.set("NumNodeColors", 256, 1, 1000));
    pGroup.add(pNoise.set("NodeNoiseMult", 0.1, 0.001, 0.2));
    pGroup.add(pNoiseAnim.set("NodeNoiseAnim", 0.1, 0, 0.5));
}

void Struct::setColors(const std::vector<ofColor> & colors) {
    for (int i=0; i<nodes.size(); i++) {
        float n = noise(posNormal(unpack(i)));
        nodes[i]->setColor(colors[n * colors.size()]);
    }
}

void Struct::initRotation(glm::vec3 maxSpeed, float rotation) {
    setRotation(maxSpeed, rotation);
    for (auto& node : nodes) {
        node->setRotation(maxSpeed, rotation);
    }
}

void Struct::update(const glm::mat4 &mat) {
    curTime = ofGetElapsedTimef();
    updateFromParams();
    Container::update(mat);
}

void Struct::updateFromParams() {
    if (pGroup.size() > 0) {
        if (lPos != pPos) {
            lPos = pPos;
            pos = lPos.get();
        }
        else if (lPos.hasExprSymbol("t")) {
            pos = lPos.get();
        }
        if (lNumNodes != pNumNodes) {
            resize();
            transform();
            initRotation();
            updateColors();
        }
        else {
            if (isTransformDirty()) {
                transform();
            }
            else if (isTransformAnim()) {
                animate();
            }
            updateColors();
        }
        //boxes.write(BOXES_RES, colors);
    }
}

void Struct::updateColors() {
    float mult = pNoise.get();
    if (mult != noiseMult) {
        noiseAnimOffset = glm::vec3(mult - ofRandom(mult*2), mult - ofRandom(mult*2), mult - ofRandom(mult*2));
    }
    noiseMult = mult;
    noiseOffset += noiseAnimOffset * pNoiseAnim.get();
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

void Struct::updateDims() {
    const glm::vec3 nodes = (glm::vec3(numNodes) * lNodeSize.get());
    const glm::vec3 spaces = (glm::vec3(numNodes) - glm::vec3(1.f)) * lNodeSpacing.get();
    dims = (nodes + spaces);
    origin = (Object::REG[(int) pReg.get()] * dims);
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

void Struct::randomize() {
    const glm::vec4 &min = pNumNodes.getMin();
    const glm::vec4 &max = pNumNodes.getMax();
    pNumNodes.set(glm::vec4(ofRandom(min.x, max.x), ofRandom(min.y, max.y), ofRandom(min.z, max.z), 1));
    pNoise.setRandom();
    pNoiseAnim.setRandom();
    pNodeSize.setRandom();
    pNodeSpacing.setRandom();
    if (pNodeDisplacement.isExplicit()) {
        pNodeDisplacement.setRandom();
    }
}

void Struct::randomizeColor() {
    Node::randomizeColor();
    pColorScheme.setRandom();
    //pNumColors.setRandom();
}
