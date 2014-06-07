#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofDisableArbTex();
    ofBackground(0, 0, 0);
    
    ofSetWindowShape(FLOOR_WIDTH, FLOOR_DEPTH);
    
    light.setPosition(0, 0, 300);
    floor.setup(FLOOR_WIDTH, FLOOR_DEPTH, 0, 0, -300);
        
    image.loadImage("shadow1.png");
    image.setImageType(OF_IMAGE_GRAYSCALE);
    image.resize(FLOOR_WIDTH, FLOOR_DEPTH);

    int step = 10; //!!!!!
    ofPixelsRef pix = image.getPixelsRef();
    for (int y = 0; y < pix.getHeight(); y += step) {
        for (int x = 0; x < pix.getWidth(); x += step) {
            if (pix.getColor(x, y).getBrightness() <= 50) {
                
                Ray ray;
                ray.set(light.getPosition(),
                        ofVec3f(x - FLOOR_WIDTH * 0.5,
                                y - FLOOR_DEPTH * 0.5,
                                -300));
                
                ray.interpolate(ofRandom(0.0, 1.0));
                rays.push_back(ray);
            }
        }
    }
    
    vector<ofVec3f> sources;
    for (int i = 0; i < rays.size(); i++) {
        sources.push_back(rays[i].getInterpolated());
    }
    
    cam.setDistance(1000);
    
    bDrawFloor = true;
    bDrawLines = true;
    
    vein.addRoot(ofVec3f(0, 0, 0));
    vein.addSources(sources);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vein.update();
    
    if (saveSeq) {
        vein.exportImage(-300, 300, FLOOR_WIDTH, FLOOR_DEPTH, FLOOR_WIDTH);
        saveSeq = false;
        cout << "saved" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    //ofBackgroundGradient(ofColor(255), ofColor(128));
    
    cam.begin();
    //ofPushMatrix();
    //ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 300);
    
    ofSetColor(255, 255, 255);
    light.draw();
    
    if (bDrawFloor) {
        ofSetColor(255, 255, 255);
        image.getTextureReference().bind();
        floor.draw();
        image.getTextureReference().unbind();
    }
    /*
    for (int i = 0; i < rays.size(); i++) {
        ofSetColor(255, 255, 255);
        glLineWidth(1);
        rays[i].draw();
        
        ofSetColor(255, 0, 0);
        glPointSize(2);
        rays[i].drawInterpolated();
    }*/
    
    vein.draw();
    
    cam.end();
    //ofPopMatrix();
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("'f'key - enable/disable floor", ofPoint(20, 20));
    ofDrawBitmapString("'l'key - enable/disable lines", ofPoint(20, 40));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'f') {
        bDrawFloor = !bDrawFloor;
    }
    
    else if (key == 'l') {
        bDrawLines = !bDrawLines;
    }
    
    else if (key == 's') {
        saveSeq = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
