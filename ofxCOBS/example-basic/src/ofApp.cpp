#include "ofApp.h"

//------------------------------------------------------------------------------
void ofApp::setup()
{

    uint8_t numValues = 20;
    uint32_t values[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    for(int i = 0; i < numValues; i++) {
        cout << values[i] << endl;
    }


    ByteBuffer buffer(sizeof(uint32_t)*numValues);

    uint32_t valuesZ[numValues];

    int i = buffer.write(values,numValues);

    memset(values,0,sizeof(uint32_t)*numValues);

    uint32_t checksum = Checksum::checksum(buffer.data(),buffer.size());

    bool b = buffer.readUInt32(values, numValues);

    
    cout << b << " << " << i << " " << checksum << " " << buffer.size() << buffer.index() << " " << buffer.capacity() << endl;

//    cout << "----" << ~0L << endl;
//
//    for(int i = 0; i < 10000; i++) {
//        size_t numValues = (size_t)ofRandom(1000);
//
//        ByteBuffer values(numValues);
//
//        for(size_t i = 0; i < values.capacity(); ++i)
//        {
//            values.write((uint8_t)ofRandom(256));
//        }
//
//        uint8_t encoded[1024];
//        uint8_t decoded[1024];
//
//        size_t numEncodedBytes = COBS::encode(values.data(), values.size(), encoded);
//        size_t numDecodedBytes = COBS::decode(encoded, numEncodedBytes, decoded);
//
//
//        ByteBuffer buffer(numValues);
//
//        size_t n = buffer.write(decoded,numDecodedBytes);
//
//        if(n != numDecodedBytes) {
//            cout << "ERROR 1" << endl;
//        }
//
//        uint32_t crc0 = Checksum::checksum(values.data(), values.size());
//        uint32_t crc1 = Checksum::checksum(decoded, numDecodedBytes);
//
//
//        if(crc0 != crc1) {
//            cout << "ERROR" << endl;
//        }
//    }

    // open the COBS serial connection
    serial.setup(0,115200);  // hope that the first one (0) is the one we want!

    LED led;
    localLEDs.assign(DEFAULT_NUM_LEDS,led);
    remoteLEDs.assign(DEFAULT_NUM_LEDS,led);

}

//------------------------------------------------------------------------------
void ofApp::update()
{
    serial.update();
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
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

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
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

//------------------------------------------------------------------------------
void ofApp::onPacket(const BufferedSerialEventArgs& packet)
{
    cout << "xyz << " << endl;
}
