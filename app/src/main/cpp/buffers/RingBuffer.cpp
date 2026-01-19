#include "RingBuffer.h"

/*
Implements a fixed-capacity single-writer, single-reader ring buffer.
Overwrite-on-full semantics are enforced by advancing the read index
when the write index catches up.
*/


template <typename T>
RingBuffer<T>::RingBuffer(size_t capacity)
    : buffer_(new T[capacity]),
      capacity_(capacity),
      writeIndex_(0),
      readIndex_(0) {}

template <typename T>
RingBuffer<T>::~RingBuffer() {
    delete[] buffer_;
}

template <typename T>
void RingBuffer<T>::push(const T& item) {
    buffer_[writeIndex_] = item;
    writeIndex_ = (writeIndex_ + 1) % capacity_;

    if (writeIndex_ == readIndex_) {
        readIndex_ = (readIndex_ + 1) % capacity_;
    }
}

template <typename T>
bool RingBuffer<T>::readLatest(T& out) const {
    if (writeIndex_ == readIndex_) {
        return false;
    }

    size_t latestIndex = (writeIndex_ + capacity_ - 1) % capacity_;
    out = buffer_[latestIndex];
    return true;
}

template <typename T>
size_t RingBuffer<T>::capacity() const {
    return capacity_;
}
