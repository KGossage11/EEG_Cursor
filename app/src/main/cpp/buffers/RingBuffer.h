#pragma once

/*
Lock-free single-writer / single-reader ring buffer.
Fixed capacity.
Overwrite-on-full semantics.
*/

#include <vector>
#include <atomic>
#include <cstddef>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
            : buffer_(capacity),
              capacity_(capacity),
              writeIndex_(0) {}

    ~RingBuffer() = default;

    void push(const T& value) {
        buffer_[writeIndex_ % capacity_] = value;
        writeIndex_.fetch_add(1, std::memory_order_release);
    }

    bool readLatest(T& out) const {
        size_t index = writeIndex_.load(std::memory_order_acquire);
        if (index == 0) {
            return false;
        }
        out = buffer_[(index - 1) % capacity_];
        return true;
    }

private:
    std::vector<T> buffer_;
    const size_t capacity_;
    std::atomic<size_t> writeIndex_;
};
