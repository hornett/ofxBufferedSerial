// =============================================================================
//
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


#include "Checksum.h"


#ifdef ARDUINO
    #define CRC_TABLE_TYPE PROGMEM prog_uint32_t
#else
    #define CRC_TABLE_TYPE uint32_t
#endif


static CRC_TABLE_TYPE crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};


//------------------------------------------------------------------------------
Checksum::Checksum(Type type) :
    _type(type),
    _checksum(~0L)
{
}

//------------------------------------------------------------------------------
Checksum::~Checksum()
{
}

//------------------------------------------------------------------------------
Checksum::Type Checksum::type() const
{
    return _type;
}

//------------------------------------------------------------------------------
uint32_t Checksum::checksum() const
{
    return ~_checksum;
}

//------------------------------------------------------------------------------
void Checksum::update(uint8_t data)
{
    _checksum = update(_checksum,data);
}

//------------------------------------------------------------------------------
void Checksum::update(const uint8_t* data, size_t size)
{
    _checksum = update(_checksum, data, size);
}

//------------------------------------------------------------------------------
uint32_t Checksum::checksum(const uint8_t* data, size_t size)
{
    Checksum checksum;
    checksum.update(data,size);
    return checksum.checksum();
}

//------------------------------------------------------------------------------
uint32_t Checksum::update(uint32_t checksum, uint8_t data)
{
    // via http://forum.arduino.cc/index.php?topic=91179.0

    uint8_t tbl_idx;

#ifdef __AVR__
    tbl_idx = checksum ^ (data >> (0 * 4));
    checksum = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (checksum >> 4);
    tbl_idx = checksum ^ (data >> (1 * 4));
    checksum = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (checksum >> 4);
#else
    tbl_idx = checksum ^ (data >> (0 * 4));
    checksum = *(crc_table + (tbl_idx & 0x0f)) ^ (checksum >> 4);
    tbl_idx = checksum ^ (data >> (1 * 4));
    checksum = *(crc_table + (tbl_idx & 0x0f)) ^ (checksum >> 4);
#endif

    return checksum;
}

//------------------------------------------------------------------------------
uint32_t Checksum::update(uint32_t checksum, const uint8_t* data, size_t size)
{
    while(size--) checksum = update(checksum,*data++);
    
    return checksum;
}
