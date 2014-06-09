//
//  Line.h
//  shadowSculpture
//
//  Created by shiraki on 2014/05/18.
//
//

#ifndef shadowSculpture_Line_h
#define shadowSculpture_Line_h

class Line {
public:
    Line() : rank(0) {}
    Line(int r) : rank(r) {}
    void addDestination(const Destination& dest) {
        destinations.push_back(dest);
    }
    
    void addDestination(const ofVec3f &dest) {
        destinations.push_back(Destination(dest));
    }
    
    void draw() {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < destinations.size(); ++i) {
            ofVec3f pos = destinations[i].position;
            glVertex3f(pos.x, pos.y, pos.z);

        }
        glEnd();
    }
    
    void setRank(int r) { rank = r; }
    int  getRank() const { return rank; }
    
    Destination * getDestinationPointer(int index) { return &destinations[index]; }
    vector<Destination> & getDestinations() { return destinations; }
    
    vector<Destination> destinations;
    int rank;
    
};


#endif
