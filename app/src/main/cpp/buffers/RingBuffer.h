#pragma once

/*
Defines the interface and contract for a fixed-capacity single-writer,
single-reader ring buffer.
Implementation details are defined in RingBuffer.cpp
*/

#include <cstddef>
#include <cstdint>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity);
    ~RingBuffer();

    // Disable copy constructor and assignment operator
    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;

    void push(const T& item);
    bool readLatest(T& out) const;
    size_t capacity() const;

private:
    T* buffer_;
    size_t capacity_;
    size_t writeIndex_;
    size_t readIndex_;
};