// =============================================================================
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "ByteBuffer.h"
#include "COBS.h"


#ifdef ARDUINO
    #if ARDUINO >= 100
        #include "Arduino.h"
    #else
        #include "WProgram.h"
    #endif

    #define _DEFAULT_PACKET_BOUNDARY  0x00
    #define _DEFAULT_BUFFER_SIZE      1024
    #define _DEFAULT_WRITE_BLOCK_SIZE 64
    #define SERIAL Stream

    typedef void (*voidFuncPtr)(ByteBuffer*);
#else
    #include "ofSerial.h"
    #include "BufferedSerialEvents.h"

    #define _DEFAULT_PACKET_BOUNDARY  0x00
    #define _DEFAULT_BUFFER_SIZE      2048
    #define _DEFAULT_WRITE_BLOCK_SIZE 0
    #define SERIAL ofSerial
#endif


class BufferedSerial: public ByteBuffer
{
public:
    BufferedSerial(size_t bufferSize = DEFAULT_BUFFER_SIZE);

    virtual ~BufferedSerial();

    void setup(size_t interface, size_t baud);
#ifndef ARDUINO
    void setup(const std::string& interface, size_t baud);
#endif

    void update();

    bool send();

#ifdef ARDUINO
    voidFuncPtr onPacketFunc;
    void setPacketHandler(void (*_onPacketFunc)(ByteBuffer*))
    {
        onPacketFunc = _onPacketFunc;
    }
    void onPacket(ByteBuffer* buffer)
    {
    }
#else
    BufferSerialEvents events;
#endif

private:
    BufferedSerial(const BufferedSerial&);
    BufferedSerial& operator=(const BufferedSerial&);

    enum {
        DEFAULT_PACKET_BOUNDARY  = _DEFAULT_PACKET_BOUNDARY,
        DEFAULT_BUFFER_SIZE      = _DEFAULT_BUFFER_SIZE,
        DEFAULT_WRITE_BLOCK_SIZE = _DEFAULT_WRITE_BLOCK_SIZE
    };

    uint8_t* _encodedBuffer;
    ByteBuffer* _buffer;

    SERIAL* _serial;

};
