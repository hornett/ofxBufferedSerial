// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
// Copyright 2011, Jacques Fortier. All rights reserved.
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


#include "COBS.h"


/// Stuffs "size" bytes of data at the location pointed to by
/// "src", writing the output to the location pointed to by
/// "dest". Returns the number of bytes written to "dest".
//------------------------------------------------------------------------------
size_t COBS::encode(const uint8_t* source, size_t size, uint8_t* destination)
{
    size_t read_index  = 0;
    size_t write_index = 1;
    size_t code_index  = 0;
    uint8_t code       = 1;

    while(read_index < size)
    {
        if(source[read_index] == 0)
        {
            destination[code_index] = code;
            code = 1;
            code_index = write_index++;
            read_index++;
        }
        else
        {
            destination[write_index++] = source[read_index++];
            code++;

            if(code == 0xFF)
            {
                destination[code_index] = code;
                code = 1;
                code_index = write_index++;
            }
        }
    }

    destination[code_index] = code;

    return write_index;
}

/// Unstuffs "size" bytes of data at the location pointed to by
/// "src", writing the output * to the location pointed to by
/// "dest". Returns the number of bytes written to "dest" if
/// "src" was successfully unstuffed, and 0 if there was an
/// error unstuffing "src".
//------------------------------------------------------------------------------
size_t COBS::decode(const uint8_t* source, size_t size, uint8_t* destination)
{
    size_t read_index  = 0;
    size_t write_index = 0;
    uint8_t code;
    uint8_t i;

    while(read_index < size)
    {
        code = source[read_index];

        if(read_index + code > size && code != 1)
        {
            return 0;
        }

        read_index++;

        for(i = 1; i < code; i++)
        {
            destination[write_index++] = source[read_index++];
        }

        if(code != 0xFF && read_index != size)
        {
            destination[write_index++] = '\0';
        }
    }
    
    return write_index;
}

////------------------------------------------------------------------------------
//size_t COBS::encode(const ByteBuffer& source, ByteBuffer& destination)
//{
//    size_t read_index  = 0;
//    size_t write_index = 1;
//    size_t code_index  = 0;
//    uint8_t code       = 1;
//
//    while(read_index < source.size())
//    {
//        if(source[read_index] == 0)
//        {
//            destination[code_index] = code;
//            code = 1;
//            code_index = write_index++;
//            read_index++;
//        }
//        else
//        {
//
//            uint8_t value;
//
//            if(source.readUInt8(value)) {
//                destination.write(value);
//            }
//
//            code++;
//
//            if(code == 0xFF)
//            {
//                destination[code_index] = code;
//                code = 1;
//                code_index = write_index++;
//            }
//        }
//    }
//
//    destination[code_index] = code;
//
//    return write_index;
//}
//
////------------------------------------------------------------------------------
//size_t COBS::decode(const ByteBuffer& source, ByteBuffer& destination)
//{
//    
//}
//
