#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    
    LED led;
    localLEDs.assign(DEFAULT_NUM_LEDS,led);
    remoteLEDs.assign(DEFAULT_NUM_LEDS,led);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    int width  = ofGetWidth();
    int height = ofGetHeight();
    
    int halfWidth  = width  / 2;
    int halfHeight = height / 2;
    
    int xSpace = 5;
    int ySpace = 5;
    
    int xOffset = xSpace;
    int yOffset = ySpace;
    
    int xIncrement = LED::DEFAULT_WIDTH  + xSpace;
    int yIncrement = LED::DEFAULT_HEIGHT + ySpace;

    
    for(size_t i = 0; i < DEFAULT_NUM_LEDS; ++i)
    {
        ofPushMatrix();
        localLEDs[i].draw(xOffset, yOffset);
        remoteLEDs[i].draw(xOffset, yOffset + halfHeight);
        
        xOffset += xIncrement;
        if(xOffset + xIncrement > ofGetWidth())
        {
            yOffset += yIncrement;
            xOffset = xSpace;
        }
        ofPopMatrix();
    }
    
    ofSetColor(255);
    ofLine(0,ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
    
    ofDrawBitmapStringHighlight("Local Values", halfWidth-50, halfHeight-20, ofColor(80),ofColor(255,255,0));
    ofDrawBitmapStringHighlight("Echoed Remote Values", halfWidth-75, height-20, ofColor(80),ofColor(255,255,0));

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'r') {
        // set random local led to randome color and send
        size_t randomIndex = (size_t)ofRandom(DEFAULT_NUM_LEDS);
        localLEDs[randomIndex].setRandomColor();
        
    } else if(key == ' ') {
        // set all leds to random color and send
        for(size_t i = 0; i < DEFAULT_NUM_LEDS; ++i) {
            localLEDs[i].setRandomColor();
        }
    } else if(key == 'c') {
        // set all leds to white
        for(size_t i = 0; i < DEFAULT_NUM_LEDS; ++i) {
            localLEDs[i].setColor(255);
        }
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}