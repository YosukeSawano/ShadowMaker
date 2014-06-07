//
//  Ray.h
//  shadowSculpture
//
//  Created by shiraki on 2014/04/08.
//
//

#ifndef shadowSculpture_Ray_h
#define shadowSculpture_Ray_h

#include "ofMain.h"

class Ray {
public:
    Ray() : index(0) {}
    virtual ~Ray(){}
    
    void set(const ofVec3f &_begin, const ofVec3f &_end, int _index = 0) {
        begin = _begin;
        end   = _end;
        index = _index;
    }
    
    void draw() {
        glBegin(GL_LINES);
        glVertex3f(begin.x, begin.y, begin.z);
        glVertex3f(end.x, end.y, end.z);
        glEnd();
    }
    
    void drawInterpolated() {
        glBegin(GL_POINTS);
        glVertex3f(interpolated.x, interpolated.y, interpolated.z);
        glEnd();
    }
    
    void interpolate(float t) {
        interpolated = begin + (end - begin) * t;
    }
    
    ofVec3f getInterpolated() const {
        return interpolated;
    }
    
    int index;
    ofVec3f begin, end;
    ofVec3f interpolated;
};

#endif
