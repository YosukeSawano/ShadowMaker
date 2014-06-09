//
//  Light.h
//  shadowSculpture
//
//  Created by shiraki on 2014/04/04.
//
//

#ifndef __shadowSculpture__Light__
#define __shadowSculpture__Light__

#include "ofMain.h"

class Light {
public:
    Light() : dir(ofVec3f(0, 1, 0)) {}
    void setPosition(int x, int y, int z) { pos.set(x, y, z); }
    void setPosition(const ofVec3f &pos)  { this->pos = pos; }
    void setDirection(const ofVec3f &dir) { this->dir = dir.normalized(); }
    void draw() { ofSphere(pos, 10); }
    
    ofVec3f getPosition() const { return pos; }
    ofVec3f * getPositionPointer() { return &pos; }
    
    ofVec3f pos;
    ofVec3f dir;
};

#endif /* defined(__shadowSculpture__Light__) */
