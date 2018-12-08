#include "Stage.hpp"
#include "ofMatrix4x4.h"

using namespace vxls;

int Stage::numInstances = 0;

Stage::Stage() {
    mesh = ofMesh::box(1, 1, 1, 1, 1, 1);
}

void Stage::update() {
    glm::mat4 mat;
    Container::update(mat);
    
    if (!transformBuffer.isAllocated()) {
        transformBuffer.allocate();
        transformBuffer.bind(GL_TEXTURE_BUFFER);
        transformBuffer.setData(getMatrices(),GL_STREAM_DRAW);
        transformTex.allocateAsBufferTexture(transformBuffer,GL_RGBA32F);
    }
    else {
        transformBuffer.setData(getMatrices(),GL_STREAM_DRAW);
    }
    
    if (!colorsBuffer.isAllocated()) {
        colorsBuffer.allocate();
        colorsBuffer.bind(GL_TEXTURE_BUFFER);
        colorsBuffer.setData(getColors(),GL_STREAM_DRAW);
        colorsTex.allocateAsBufferTexture(colorsBuffer,GL_RGBA32F);
    }
    else {
        colorsBuffer.setData(getColors(),GL_STREAM_DRAW);
    }
    
    transformBuffer.updateData(0, getMatrices());
    colorsBuffer.updateData(0, getColors());
    
    camera.update(mat);
}
