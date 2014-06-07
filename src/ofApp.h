#pragma once

#include "ofMain.h"
#include "Floor.h"
#include "Light.h"
#include "Ray.h"
#include "Vein.h"

const int FLOOR_WIDTH  = 600;
const int FLOOR_DEPTH  = 600;
const int FLOOR_POSY   = -300;

typedef vector<Ray> Rays;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    Floor floor;
    Light light;
    Rays  rays;
    
    ofImage image;
    
    bool saveSeq;
    
    bool bDrawFloor;
    bool bDrawLines;
    
    Vein vein;
};
