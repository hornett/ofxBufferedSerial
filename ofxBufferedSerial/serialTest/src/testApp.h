#pragma once

#include "ofMain.h"

/*
 
 B0     -> (uint8_t)  : The type of the byte array
 : 0 : uint8_t  array
 : 1 : uint16_t array
 : 2 : uint32_t array
 : 3 : int8_t   array
 : 4 : int16_t  array
 : 5 : int32_t  array
 
 B1, B2     -> (uint16_t) : The length of the payload (up to 65536)
 B3...BN    -> Payload bytes to be interpreted based on B0
 BN+1,BN+2  -> Payload Checksum
 */


class LED
{
public:
    LED(int width = DEFAULT_WIDTH,
        int height = DEFAULT_HEIGHT,
        const ofColor& color = ofColor(255,255,255,255)) :
    _width(width),
    _height(height),
    _color(color)
    {
    }
    
    void setRandomColor()
    {
        unsigned char r = ofRandom(0,255);
        unsigned char g = ofRandom(0,255);
        unsigned char b = ofRandom(0,255);
        unsigned char a = 255;
        
        _color.set(r,g,b,a);
    }
    
    void setColor(const ofColor& color)
    {
        _color = color;
    }
    
    void draw(int x, int y)
    {
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(x,y);
        
        ofSetColor(_color);
        ofRect(0,0,_width,_height);
        
        ofPopStyle();
        ofPopMatrix();
    }
    
    enum
    {
        DEFAULT_WIDTH  = 32,
        DEFAULT_HEIGHT = 16
    };
    
protected:
    int _width;
    int _height;
    ofColor _color;
};


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
//    
//    void onPacket(const BufferedSerialEventArgs& packet);
//    
//    BufferedSerial serial;
//    ByteBuffer buffer;
    
    std::vector<LED> localLEDs;
    std::vector<LED> remoteLEDs;
    
    enum
    {
        DEFAULT_NUM_LEDS = 512
    };
		
};
