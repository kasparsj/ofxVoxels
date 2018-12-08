#include "Grid.hpp"

using namespace vxls;

int Grid::numInstances = 0;

void Grid::write(int res, int z, vector<ofColor> & colors) {
    for (int i=0; i<res; i++) {
        for (int j=0; j<res; j++) {
            int k = 0;
            getVoxel(res*2+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*2+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*2+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*2+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*2+i, res*6+j, z)->setColor(colors[++k]);
            getVoxel(res*3+i, res*6+j, z)->setColor(colors[++k]);
            
            getVoxel(res*5+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*5+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*5+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*5+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*5+i, res*6+j, z)->setColor(colors[++k]);
            
            getVoxel(res*7+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*8+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*7+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*7+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*8+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*7+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*7+i, res*6+j, z)->setColor(colors[++k]);
            getVoxel(res*8+i, res*6+j, z)->setColor(colors[++k]);
            
            getVoxel(res*10+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*11+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*12+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*10+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*12+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*10+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*11+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*12+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*10+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*10+i, res*6+j, z)->setColor(colors[++k]);
           
            getVoxel(res*15+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*14+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*14+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*15+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*14+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*14+i, res*6+j, z)->setColor(colors[++k]);
            getVoxel(res*16+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*16+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*16+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*16+i, res*6+j, z)->setColor(colors[++k]);
           
            getVoxel(res*19+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*19+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*19+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*19+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*18+i, res*6+j, z)->setColor(colors[++k]);
           
            getVoxel(res*22+i, res*2+j, z)->setColor(colors[++k]);
            getVoxel(res*21+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*21+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*22+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*21+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*21+i, res*6+j, z)->setColor(colors[++k]);
            getVoxel(res*23+i, res*3+j, z)->setColor(colors[++k]);
            getVoxel(res*23+i, res*4+j, z)->setColor(colors[++k]);
            getVoxel(res*23+i, res*5+j, z)->setColor(colors[++k]);
            getVoxel(res*23+i, res*6+j, z)->setColor(colors[++k]);
        }
    }
    
    shiftColor(4*res, 12*res);
}

void Grid::shiftColor(int x, int y) {
//    vector<Box> temp;
//    temp.resize(size());
//    copy(&boxes[0], &boxes[0]+size(),&temp[0]);
//    for (int i=0; i<boxesX; i++) {
//        for (int j=0; j<boxesY; j++) {
//            int ix = i + x < boxesX ? i + x : i + x - boxesX;
//            int jy = j + y < boxesY ? j + y : j + y - boxesY;
//            nodes[ix*boxesY+jy]->setColor(temp[i*boxesY+j].color);
//        }
//    }
}

//void Grid::draw() {
//    ofBoxPrimitive box3d;
//    box3d.set(20);
//
//    for (int i=0; i<BOXES_X*res; i++) {
//        for (int j=0; j<BOXES_Y*res; j++) {
//            //ofSetColor(nodes[i][j].color);
//
//            box3d.setSideColor(box3d.SIDE_FRONT, nodes[i][j].color);
//            box3d.setSideColor(box3d.SIDE_LEFT, nodes[i][j].color);
//            box3d.setSideColor(box3d.SIDE_RIGHT, nodes[i][j].color);
//            box3d.setSideColor(box3d.SIDE_TOP, nodes[i][j].color);
//            box3d.setSideColor(box3d.SIDE_BACK, nodes[i][j].color);
//            box3d.setSideColor(box3d.SIDE_BOTTOM, nodes[i][j].color);
//
//            ofQuaternion orientation = ofQuaternion(nodes[i][j].rotationX, ofVec3f(1.0, 0.0, 0.0), nodes[i][j].rotationY, ofVec3f(0.0, 1.0, 0.0), nodes[i][j].rotationZ, ofVec3f(0.0, 0.0, 1.0));
//            box3d.setOrientation(orientation);
//            box3d.setPosition(boxes[i][j].x * (box3d.getWidth() + 15), nodes[i][j].y * (box3d.getHeight()+ 15), 0);
//            box3d.draw();
//
//        }
//    }
//}
