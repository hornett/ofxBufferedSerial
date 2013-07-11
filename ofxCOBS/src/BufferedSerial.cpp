// =============================================================================
// COBS Implementation
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


#include "BufferedSerial.h"


//------------------------------------------------------------------------------
BufferedSerial::BufferedSerial(size_t bufferSize) :
    ByteBuffer(bufferSize),
    _buffer(NULL),
    _serial(NULL)
{
    _buffer = new ByteBuffer(bufferSize);
//    _encodedBuffer = new uint8_t[bufferSize + bufferSize / 254];

#ifdef ARDUINO
    onPacketFunc = NULL;
#else
    _serial = new ofSerial();
#endif
}

//------------------------------------------------------------------------------
BufferedSerial::~BufferedSerial()
{
    delete _buffer;
    _buffer = NULL;

#ifndef ARDUINO
    delete _serial;
    _serial = NULL;
#endif
}

//------------------------------------------------------------------------------
void BufferedSerial::setup(size_t interface, size_t baud)
{
#ifdef ARDUINO
    switch(interface) {
#if defined(UBRR1H)
        case 1:
            Serial1.begin(baud);
            _serial = &Serial1;
            break;
#endif
#if defined(UBRR2H)
        case 2:
            Serial1.begin(baud);
            _serial = &Serial2;
            break;
#endif
#if defined(UBRR3H)
        case 3:
            Serial1.begin(baud);
            _serial = &Serial3;
            break;
#endif
        case 0:
        default:
            Serial.begin(baud);
            _serial = &Serial;
    }
#else
    _serial->setup(interface, baud);
#endif

}

#ifndef ARDUINO
//------------------------------------------------------------------------------
void BufferedSerial::setup(const std::string& interface, size_t baud)
{
    _serial->setup(interface, baud);
}
#endif

//------------------------------------------------------------------------------
void BufferedSerial::update()
{
    if(_serial == NULL) return;

    while(_serial->available() > 0)
    {
#ifdef ARDUINO
        uint8_t data = _serial->read();
#else
        uint8_t data = _serial->readByte();
#endif
        // check for packet boundary
        if(data == DEFAULT_PACKET_BOUNDARY)
        {
            

#ifdef ARDUINO
            if(onPacketFunc != NULL) {
                onPacketFunc(_buffer);
            }
#else
            BufferedSerialEventArgs args(*_buffer);
            ofNotifyEvent(events.onPacket, args, this);
#endif
            _buffer->clear();
        }
        else
        {
            _buffer->write(data);
        }
    }
}

//------------------------------------------------------------------------------
bool BufferedSerial::send()
{
    if(_serial == NULL) return;

    bool bSuccess = false;

    size_t encodedBufferSize = size() + size() / 254;
    uint8_t encodedBuffer[encodedBufferSize]; // worst case COBS
    size_t numEncoded = COBS::encode(data(), size(), encodedBuffer);

    if(numEncoded > 0)
    {
        if(_serial->writeByte(DEFAULT_PACKET_BOUNDARY) &&
           _serial->writeBytes(encodedBuffer,numEncoded) == numEncoded)
        {
            bSuccess = true;
        }
    }
    else
    {
        // error
    }

    return bSuccess;
}
