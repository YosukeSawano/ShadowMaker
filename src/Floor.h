//
//  Floor.h
//  shadowSculpture
//
//  Created by shiraki on 2014/04/03.
//
//

#ifndef __shadowSculpture__Floor__
#define __shadowSculpture__Floor__

#include <iostream>
#include "ofMain.h"

class Floor : public ofVboMesh {
public:
    Floor(){}
    
    void setup(int w, int h, int x, int y, int z) {
        
        clear();
        setMode(OF_PRIMITIVE_TRIANGLES);
        
        ofVec3f nw = ofVec3f(x + -w*0.5, y + h*0.5, z);
        ofVec3f ne = ofVec3f(x + w*0.5,  y + h*0.5, z);
        ofVec3f sw = ofVec3f(x + -w*0.5, y + -h*0.5, z);
        ofVec3f se = ofVec3f(x + w*0.5,  y + -h*0.5, z);
        
        addVertex(nw);
        addTexCoord(ofVec2f(0, 1));
        addColor(ofColor::white);
        
        addVertex(ne);
        addTexCoord(ofVec2f(1, 1));
        addColor(ofColor::white);
        
        addVertex(sw);
        addTexCoord(ofVec2f(0, 0));
        addColor(ofColor::white);
        
        addVertex(se);
        addTexCoord(ofVec2f(1, 0));
        addColor(ofColor::white);
        
        addTriangle(0, 1, 2);
        addTriangle(3, 2, 1);
        
    }
    
private:
    int width, depth;
    int posY;
};
#endif /* defined(__shadowSculpture__Floor__) */
