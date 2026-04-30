#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace dsa {

template <class T>
class Queue {
public:
    Queue() : buffer_(nullptr), capacity_(0), head_(0), tail_(0), size_(0) {}

    ~Queue() { delete[] buffer_; }

    void enqueue(const T& value) {
        if (size_ == capacity_) resize();
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void dequeue() {
        if (empty()) throw std::out_of_range("Queue is empty");
        head_ = (head_ + 1) % capacity_;
        --size_;
    }

    T& front() {
        if (empty()) throw std::out_of_range("Queue is empty");
        return buffer_[head_];
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("Queue is empty");
        return buffer_[head_];
    }

    bool empty() const { return size_ == 0; }

    std::size_t size() const { return size_; }

private:
    T* buffer_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t size_;

    void resize() {
        std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* newBuffer = new T[newCap];

        for (std::size_t i = 0; i < size_; ++i)
            newBuffer[i] = buffer_[(head_ + i) % capacity_];

        delete[] buffer_;
        buffer_ = newBuffer;
        capacity_ = newCap;
        head_ = 0;
        tail_ = size_;
    }
};

} // namespace dsa
