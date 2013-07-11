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


#include "ByteBuffer.h"


//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(size_t capacity) :
    _data(0),
    _capacity(capacity),
    _size(0),
    _index(0)
{
    _data = new uint8_t[_capacity];
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(uint8_t* data, size_t size) :
    _data(0),
    _capacity(size),
    _size(0),
    _index(0)
{
    _data = new uint8_t[size];
    _write(data, size);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(const ByteBuffer& that) :
    _data(0),
    _capacity(that._capacity),
    _size(that._size),
    _index(that._index)
{
    _data = new uint8_t[_capacity];
    memcpy(_data,that._data,that._capacity);
}

//------------------------------------------------------------------------------
ByteBuffer& ByteBuffer::operator=(const ByteBuffer& that)
{
    uint8_t* newData = new uint8_t[that._capacity];
    memcpy(that._data,newData,that._capacity);
    delete[] _data;
    _data     = newData;
    _capacity = that._capacity;
    _size     = that._size;
    _index    = that._index;
    return *this;
}

//------------------------------------------------------------------------------
ByteBuffer::~ByteBuffer()
{
    delete[] _data;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::_write(const void* source, size_t size)
{
    if(_size + size <= _capacity)
    {
        memcpy(_data+_size,source,size);
        _size += size;
        return size;
    }
    else return 0;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::_read(void* destination, size_t size) const
{
    if(_capacity - _index >= size)
    {
        memcpy(destination, _data + _index, size);
        _index += size;
        return size;
    }
    else return 0;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::set(const uint8_t* data, size_t size)
{
    clear();
    return _write(data, size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(uint8_t data)
{
    return _write(&data, sizeof(uint8_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(uint16_t data)
{
    return _write(&data, sizeof(uint16_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(uint32_t data)
{
    return _write(&data, sizeof(uint32_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(uint64_t data)
{
    return _write(&data, sizeof(uint64_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(int8_t data)
{
    return _write(&data, sizeof(int8_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(int16_t data)
{
    return _write(&data, sizeof(int16_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(int32_t data)
{
    return _write(&data, sizeof(int32_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(int64_t data)
{
    return _write(&data, sizeof(int64_t));
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const uint8_t* data, size_t size)
{
    return _write(&data, sizeof(uint8_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const uint16_t* data, size_t size)
{
    return _write(&data, sizeof(uint16_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const uint32_t* data, size_t size)
{
    return _write(&data, sizeof(uint32_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const uint64_t* data, size_t size)
{
    return _write(&data, sizeof(uint64_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const int8_t* data, size_t size)
{
    return _write(&data, sizeof(int8_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const int16_t* data, size_t size)
{
    return _write(&data, sizeof(int16_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const int32_t* data, size_t size)
{
    return _write(&data, sizeof(int32_t) * size);
}

//------------------------------------------------------------------------------
size_t ByteBuffer::write(const int64_t* data, size_t size)
{
    return _write(&data, sizeof(int64_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt8(uint8_t& value) const
{
    return _read(&value,sizeof(uint8_t)) == sizeof(uint8_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt16(uint16_t& value) const
{
    return _read(&value,sizeof(uint16_t)) == sizeof(uint16_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt32(uint32_t& value) const
{
    return _read(&value,sizeof(uint32_t)) == sizeof(uint32_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt64(uint64_t& value) const
{
    return _read(&value,sizeof(uint64_t)) == sizeof(uint64_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt8(int8_t& value) const
{
    return _read(&value,sizeof(int8_t)) == sizeof(int8_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt16(int16_t& value) const
{
    return _read(&value,sizeof(int16_t)) == sizeof(int16_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt32(int32_t& value) const
{
    return _read(&value,sizeof(int32_t)) == sizeof(int32_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt64(int64_t& value) const
{
    return _read(&value,sizeof(int64_t)) == sizeof(int64_t);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt8(uint8_t* destination, size_t size) const
{
    return _read(destination,sizeof(uint8_t) * size) == (sizeof(uint8_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt16(uint16_t* destination, size_t size) const
{
    return _read(destination,sizeof(uint16_t) * size) == (sizeof(uint16_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt32(uint32_t* destination, size_t size) const
{
    return _read(destination,sizeof(uint32_t) * size) == (sizeof(uint32_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readUInt64(uint64_t* destination, size_t size) const
{
    return _read(destination,sizeof(uint64_t) * size) == (sizeof(uint64_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt8(int8_t* destination, size_t size) const
{
    return _read(destination,sizeof(int8_t) * size) == (sizeof(int8_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt16(int16_t* destination, size_t size) const
{
    return _read(destination,sizeof(int16_t) * size) == (sizeof(int16_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt32(int32_t* destination, size_t size) const
{
    return _read(destination,sizeof(int32_t) * size) == (sizeof(int32_t) * size);
}

//------------------------------------------------------------------------------
bool ByteBuffer::readInt64(int64_t* destination, size_t size) const
{
    return _read(destination,sizeof(int64_t) * size) == (sizeof(int64_t) * size);
}

//------------------------------------------------------------------------------
const uint8_t& ByteBuffer::operator[](size_t index) const
{
    return _data[index];
}

//------------------------------------------------------------------------------
const uint8_t* ByteBuffer::data() const
{
    return _data;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::capacity() const
{
    return _capacity;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::size() const
{
    return _size;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::index() const
{
    return _index;
}

//------------------------------------------------------------------------------
void ByteBuffer::resize(size_t size)
{
    _capacity = size;

    if(_size > _capacity)
    {
        _size = _capacity;

        if(_index > _size)
        {
            _index = _size;
        }
    }

    uint8_t* _data_new = new uint8_t[_capacity];

    memcpy(_data_new,_data,sizeof(uint8_t) * _size);

    delete [] _data;
    _data = _data_new;
}

//------------------------------------------------------------------------------
bool ByteBuffer::empty() const
{
    return _size == 0;
}

//------------------------------------------------------------------------------
bool ByteBuffer::full() const
{
    return _size == _capacity;
}

//------------------------------------------------------------------------------
void ByteBuffer::rewind() const
{
    _index = 0;
}

//------------------------------------------------------------------------------
void ByteBuffer::clear()
{
    _size = 0;
    _index = 0;
}

//------------------------------------------------------------------------------
ByteBuffer::ByteOrder ByteBuffer::byteOrder() const
{
    return LITTLE_ENDIAN_BYTE_ORDER;
}

