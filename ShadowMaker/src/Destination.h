//
//  Destination.h
//  shadowSculpture
//
//  Created by shiraki on 2014/05/18.
//
//

#ifndef shadowSculpture_Destination_h
#define shadowSculpture_Destination_h

#include "ofMain.h"

class Destination {
    typedef ofVec3f Position;
    typedef ofVec3f Difference;
public:
    Destination() : position(ofVec3f(0, 0, 0)), difference(ofVec3f(0, 0, 0)), bGrowing(false), bNewBranch(false), counts(0) {}
    Destination(const ofVec3f &p) : position(p), difference(ofVec3f(0, 0, 0)), bGrowing(false), bNewBranch(false), counts(0) {}
    //Destination(const Destination &d) : age(0), bGrowing(false), bNewBranch(false) {}
    
    Position    position;
    Difference  difference;
    float radius;
    bool  bGrowing;
    bool  bNewBranch;
    
    ofVec3f getPosition() const { return position; }
    void setPosition(const ofVec3f &pos) { position = pos; }
    
    int counts;
    void addDifference(const ofVec3f &diff) {
        difference += diff;
        counts++;
    }
    
    ofVec3f getAverageDifference() {
        return difference / counts;
    }
    
    ofVec3f getDifference() const { return difference; }
    void setDifference(const ofVec3f &diff) { difference = diff; }
    
    float getRadius() const { return radius; }
    void  setRadius(float r) { radius = r; }
    
    void isGrowing(bool growing) { bGrowing = growing; }
    bool isGrowing() const { return bGrowing; }
    void isNewBranch(bool branch) { bNewBranch = branch; }
    bool isNewBranch() const { return bNewBranch; }
    
    void reset() {
        bGrowing   = false;
        bNewBranch = false;
        difference.set(0, 0, 0);
        counts = 0;
    }
    
    void draw() {}
    
};


#endif
