#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace dsa {

template <class T>
class Deque {
public:
    Deque() : buffer_(nullptr), capacity_(0), head_(0), tail_(0), size_(0) {}

    ~Deque() { delete[] buffer_; }

    void push_front(const T& value) {
        if (size_ == capacity_) resize();
        head_ = (head_ + capacity_ - 1) % capacity_;
        buffer_[head_] = value;
        ++size_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) resize();
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        head_ = (head_ + 1) % capacity_;
        --size_;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        tail_ = (tail_ + capacity_ - 1) % capacity_;
        --size_;
    }

    T& front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return buffer_[head_];
    }

    T& back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return buffer_[(tail_ + capacity_ - 1) % capacity_];
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
