#pragma once

/*
Defines a single-writer, single-reader latest-value buffer.
This buffer guarantees that the reader always observes the most
recently written intent, with no backlog or queueing semantics.
*/

template <typename T>
class IntentBuffer {
public:
    IntentBuffer();
    ~IntentBuffer() = default;

    IntentBuffer(const IntentBuffer&) = delete;
    IntentBuffer& operator=(const IntentBuffer&) = delete;

    void write(const T& value);
    bool read(T& out) const;

private:
    T value_;
    bool hasValue_;
};

template <typename T>
IntentBuffer<T>::IntentBuffer()
    : hasValue_(false) {}

template <typename T>
void IntentBuffer<T>::write(const T& value) {
    value_ = value;
    hasValue_ = true;
}

template <typename T>
bool IntentBuffer<T>::read(T& out) const {
    if (!hasValue_) {
        return false;
    }
    out = value_;
    return true;
}
