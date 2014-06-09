//
//  Vein.h
//  shadowSculpture
//
//  Created by shiraki on 2014/05/17.
//
//

//
//  Vein.h
//  shadowSculpture
//
//  Created by shiraki on 2014/05/17.
//
//

#ifndef shadowSculpture_Vein_h
#define shadowSculpture_Vein_h

#include "ofMain.h"
#include "Destination.h"
#include "Line.h"

const float MIN_DIST = 2;
const float GROWING_STEP = 2;

class Vein {
    typedef vector<Destination> Destinations;
    typedef vector<ofVec3f> Sources;
    typedef vector<Line> Lines;
    typedef vector<Destination>::iterator DestinationIterator;
    typedef vector<ofVec3f>::iterator SourceIterator;
    typedef vector<Line>::iterator LineIterator;
    
public:
    
    vector<Line> lines;
    vector<Destination> destinations;
    vector<ofVec3f> sources;
    vector<ofMesh> Mesh;
    float radius;
    int resolution;
    Vein(){
        radius=10.0;
        resolution=10;
    }
    
    void addRoot(const ofVec3f root) {
        Line line(0);
        line.addDestination(root);
        lines.push_back(line);
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        Mesh.push_back(mesh);
    }
    
    void addSources(const vector<ofVec3f> &_sources) { sources = Sources(_sources); }
    
    void update() {
        
        if (sources.empty()) return;
        
        SourceIterator sItr = sources.begin();
        while (sItr != sources.end()) {
                
            int     targetLine = -1;
            int     targetDest = -1;
            bool    isDead     = false;
            bool    bNewRam    = false;
            float   maxDist    = INT_MAX;
            ofVec3f minDiff    = ofVec3f(0, 0, 0);
                
            LineIterator lItr = lines.begin();
            for(; lItr != lines.end(); ++lItr) {
                    
                Destinations destinations = lItr->getDestinations();
                DestinationIterator dItr = max(destinations.begin(), destinations.end() - 2); //lineのラスト２つを見れば良いのでは
                for (; dItr != destinations.end(); ++dItr) {
                    
                    ofVec3f diff = *sItr - dItr->position;
                    float   dist = diff.length();
                    
                    //distance between source and destination is shorter than MIN_DIST, source is killed
                    if (dist <= MIN_DIST) {
                        isDead = true;
                        break;
                    } else if (dist < maxDist) {
                        isDead = false;
                        targetLine = lItr - lines.begin();
                        targetDest = dItr - destinations.begin();
                        if (targetDest != destinations.size() - 1) bNewRam = true; //top of line?
                        else bNewRam = false;
                            
                        maxDist = dist;
                        minDiff = diff;
                    }
                }
                if (isDead) break;
            }
            
            if (isDead) {
                sItr = sources.erase(sItr); //delete and next source
            } else {
                Destination *dst = lines[targetLine].getDestinationPointer(targetDest);
                dst->addDifference(minDiff);
                dst->isGrowing(true);
                dst->isNewBranch(bNewRam);
                ++sItr;
            }
        }
        grow();
    }
    
    void grow() {
        int size = lines.size();
        for (int i = 0; i < size; i++) {
            int size2 = lines[i].getDestinations().size();
            for (int j = 0; j < size2; j++) {
                Destination *dst = lines[i].getDestinationPointer(j);
                if (dst->isGrowing()) {
                    
                    ofVec3f start     = dst->getPosition();
                    ofVec3f direction = dst->getDifference().normalized();//dst->getAverageDifference();
                    ofVec3f end       = start + direction * GROWING_STEP;
                    ofVec3f ze = ofVec3f(0, 0, 1);
                    float lxy=sqrt(direction.x*direction.x+direction.y*direction.y);
                    float zangle=acos(direction.z);
                    float xangle=acos(direction.x/lxy);
//                    float angle=ze.angleRad(direction);
                    if (dst->isNewBranch()) {
                        Line newLine(lines[j].getRank()+1);
                        newLine.addDestination(start);
                        newLine.addDestination(end);
                        lines.push_back(newLine);
                        ofMesh newMesh;

                        newMesh.setMode(OF_PRIMITIVE_TRIANGLES);
                        for (int Nres=0; Nres<resolution; Nres++) {
                            float theta=2.*pi/(resolution-1.)*Nres;
                            float x=radius*cos(theta);
                            float y=radius*sin(theta);
                            float z=0.;
                            ofVec3f pos=ofVec3f(x,y,z);
                            pos.x= pos.x*cos(zangle)+pos.z*sin(zangle);
                            pos.z=-pos.x*sin(zangle)+pos.z*cos(zangle);
                            pos.x= pos.x*cos(xangle)-pos.y*sin(xangle);
                            pos.y= pos.x*sin(xangle)+pos.y*sin(xangle);
                            pos.x+=end.x;
                            pos.y+=end.y;
                            pos.z+=end.z;
//                            pos.rotate(angle, end, ze);
                            newMesh.addVertex(pos);
                            newMesh.addColor(ofColor((j * Nres) % 2 == 0 ? 255 : 0));
                        }
                        
                        Mesh.push_back(newMesh);
                    } else {
                        lines[i].addDestination(end);
                        for (int Nres=0; Nres<resolution; Nres++) {
                            float theta=2.*pi/(resolution-1)*Nres;
                            float x=radius*cos(theta);
                            float y=radius*sin(theta);
                            float z=0.;
                            ofVec3f pos=ofVec3f(x,y,z);
                            pos.x= pos.x*cos(zangle)+pos.z*sin(zangle);
                            pos.z=-pos.x*sin(zangle)+pos.z*cos(zangle);
                            pos.x= pos.x*cos(xangle)-pos.y*sin(xangle);
                            pos.y= pos.x*sin(xangle)+pos.y*sin(xangle);
                            pos.x+=end.x;
                            pos.y+=end.y;
                            pos.z+=end.z;
//                            pos.rotate(angle, end, ze);
                            Mesh[i].addVertex(pos);
                            Mesh[i].addColor(ofColor((j * Nres) % 2 == 0 ? 255 : 0));
                        }
                        
                    }
                }
                dst->reset();
            }
        }
        for (int i = 0; i < Mesh.size(); i++) {
//            int size2 = lines[i].getDestinations().size();
            int size2 = Mesh[i].getNumVertices()/resolution;
            for (int j = 0; j < size2-1; j++) {
                for (int k = 0; k < resolution; k++) {
                    int sw=j*resolution+k;
                    int se=sw+1;
                    if (j+1==resolution) {
                        se-=resolution;
                    }
                    int nw=sw+resolution;
                    int ne=se+resolution;
                    Mesh[i].addTriangle(sw, se, nw);
                    Mesh[i].addTriangle(nw, se, ne);
                }
            }
        }
    }
    
    void draw() {
//        ofSetColor(255, 0, 0);
//        glEnable(GL_DEPTH_TEST);
        for (int i = 0; i < Mesh.size(); i++) {
            Mesh[i].draw();
//            Mesh[i].drawWireframe();
//            Mesh[i].drawFaces();
        }
//        for (int i = 0; i < lines.size(); i++) {
//            Line line = lines[i];
//            glBegin(GL_LINE_STRIP);
//            for (int j = 0; j < line.getDestinations().size(); j++) {
//                ofVec3f position = lines[i].getDestinationPointer(j)->getPosition();
//                glVertex3f(position.x, position.y, position.z);
////                printf("i:%3d j:%3d  x:%5f y:%5f z:%5f\n", i, j,position.x, position.y, position.z);
//            }
//            glEnd();
//        }
    }
    
    bool exportImage(float start, float end, int w, int h, int num) {

        ofFbo exported;
        exported.allocate(w, h);
        exported.begin();
        ofClear(0, 0, 0);
        exported.end();
        
        cout << "saving..." << endl;
        float step = (end - start) / (float)num;
        for (int i = 0; i < num; i++) {
            ofVec3f p(0, 0, start + step * i);
            
            cout << p << endl;
            exported.begin();
            ofClear(0, 0, 0, 255);
            ofPushMatrix();
            ofTranslate(w * 0.5, h * 0.5, -p.z);
        
            cout << i << " / " << num << endl;
            
            for (int j = 0; j < lines.size(); j++) {
                
                int   rank = lines[j].getRank();
                float radius = max(5 - rank, 0);
                Destinations vertices = lines[j].getDestinations();
                for (int k = 1; k < vertices.size(); k++) {
                    ofVec3f a = vertices[k-1].getPosition(); //end
                    ofVec3f b = vertices[k].getPosition();   //start
                    ofVec3f ab = b - a;
                    
                    ofVec3f pa = p - a;
                    ofVec3f pb = p - b;
                    
                    float az = pa.z;
                    float bz = pb.z;
                    
                    if (abs(az) < 0.000001) az = 0;
                    if (abs(bz) < 0.000001) bz = 0;
                    
                    if (az == 0.0 && bz == 0.0) continue; //line on plane
                    else if ((az >= 0.0 && bz <= 0.0) || (az <= 0.0 && bz >= 0.0)) ;//crossing
                    else continue;
                    
                    double t = abs(az) / (abs(az) + abs(bz));
                    ofVec3f result = a + ab * t;
                    
                    ofSetColor(255, 255, 255, 255);
                    ofSphere(result, radius);
                }
            }
            
            ofPopMatrix();
            exported.end();
            
            ofPixels pix;
            exported.readToPixels(pix);
            ofSaveImage(pix, "seq_" + ofToString(i) + ".png");
            
        }
        
    }
    
};

#endif

