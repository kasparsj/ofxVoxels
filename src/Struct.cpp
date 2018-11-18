#include "Struct.hpp"
#include "Strings.hpp"
#include "Utils.hpp"

using namespace ofxVoxels;

void Struct::resize(const vec4 &numNodes) {
    this->numNodes = numNodes;
    const int count = countNodes();
    Object::resizeNodes(count);
    if (children.size() == 0) {
        matrices.clear();
        matrices.resize(count);
        colors.clear();
        colors.resize(count);
    }
}

void Struct::setupParameterGroup() {
    Object::setupParameterGroup();
    pGroup.add(pColor.set(Strings::NODE_COLOR, ofColor::magenta));
    pGroup.add(pColorScheme.set(Strings::NODE_COLOR_SCHEME, 0, 0, (ColorWheelSchemes::SCHEMES.size() - 1)));
    pGroup.add(pNumColors.set("NumNodeColors", 256, 1, 1000));
    pGroup.add(pNoise.set("NodeNoiseMult", 0.1, 0.001, 0.2));
    pGroup.add(pNoiseAnim.set("NodeNoiseAnim", 0.1, 0, 0.5));
}

void Struct::setColors(const vector<ofColor> & colors) {
    for (int i=0; i<nodes.size(); i++) {
        const shared_ptr<Node> &box = nodes[i];
        float n = noise(box->getPosition() / (lNodeSize.value() + lNodeSpacing.value()));
        box->setColor(colors[n * colors.size()]);
    }
}

void Struct::initRotation(vec3 maxSpeed, float rotation) {
    setRotation(maxSpeed, rotation);
    for (auto& node : nodes) {
        node->setRotation(maxSpeed, rotation);
    }
}

void Struct::update(const glm::mat4 &mat) {
    updateFromParams();
    Container::update(mat);
}

void Struct::updateFromParams() {
    if (pGroup.size() > 0) {
        glm::ivec4 iNumNodes = pNumNodes.get();
        if (iNumNodes != numNodes) {
            resize(iNumNodes);
            transform();
            initRotation();
            
            updateColors();
        }
        else {
            updateColors();
            if (isTransformDirty()) {
                transform();
            }
        }
        //boxes.write(BOXES_RES, colors);
    }
}

void Struct::updateColors() {
    float mult = pNoise.get();
    if (mult != noiseMult) {
        noiseAnimOffset = vec3(mult - ofRandom(mult*2), mult - ofRandom(mult*2), mult - ofRandom(mult*2));
    }
    noiseMult = mult;
    noiseOffset += noiseAnimOffset * pNoiseAnim.get();
    vector<ofColor> colors;
    if (pNumColors.get() > 1) {
        scheme = ColorWheelSchemes::SCHEMES[pColorScheme.get()];
        scheme->setPrimaryColor(pColor.get());
        colors = scheme->interpolate(pNumColors.get());
    }
    else {
        colors.push_back(pColor.get());
    }
    setColors(colors);
}

void Struct::updateDims() {
    const glm::vec3 nodes = (glm::vec3(numNodes) * lNodeSize.value());
    const glm::vec3 spaces = (glm::vec3(numNodes) - vec3(1.f)) * lNodeSpacing.value();
    dims = (nodes + spaces);
    origin = (Object::REG[(int) pReg.get()] * dims);
    int l = (int) Registration::BACK;
    vector<float> distances;
    distances.push_back(0);
    distances.push_back(dims.y / 2.f);
    distances.push_back(dims.y / 2.f);
    distances.push_back(dims.x / 2.f);
    distances.push_back(dims.x / 2.f);
    distances.push_back(dims.z / 2.f);
    distances.push_back(dims.z / 2.f);
    sidesMatrix.resize(l+1);
    for (int side=0; side<=l; side++) {
        sidesMatrix[side] = glm::translate(glm::mat4(1.0), toGlm(vec3(0, distances[side], 0)));
        sidesMatrix[side] *= ROT[side];
    }
}

void Struct::randomize() {
    const vec4 &min = pNumNodes.getMin();
    const vec4 &max = pNumNodes.getMax();
    pNumNodes.set(vec4(ofRandom(min.x, max.x), ofRandom(min.y, max.y), ofRandom(min.z, max.z), 1));
    pNoise.setRandom();
    pNoiseAnim.setRandom();
    pNodeSize.setRandom();
    pNodeSpacing.setRandom();
    if (pNodeDisplacement.is_set()) {
        pNodeDisplacement.setRandom();
    }
}

void Struct::randomizeColor() {
    Node::randomizeColor();
    pColorScheme.setRandom();
    //pNumColors.setRandom();
}
