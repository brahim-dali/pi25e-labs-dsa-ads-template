//
// Created by marius on 1/26/26.
//

// Supported by GCC, Clang, MSVC

// DynamicArray<T>
// ----------------
// A simple resizable array implementation.
// Implemented as a template so it can store elements of any type T.
// Used to demonstrate memory allocation, resizing, and basic container design.
// This is an educational implementation (not a replacement for std::vector).

#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>   // for std::move

namespace dsa {

template <class T>
class DynamicArray {
public:
   
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}

    
    ~DynamicArray() {
        delete[] data_;
    }

   
    DynamicArray(const DynamicArray& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {

        if (capacity_ > 0) {
            data_ = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;

        T* newData = nullptr;

        if (other.capacity_ > 0) {
            newData = new T[other.capacity_];
            for (std::size_t i = 0; i < other.size_; ++i) {
                newData[i] = other.data_[i];
            }
        }

        delete[] data_;

        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

   
    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    
    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }

    
    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

   
    T& at(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("Index out of bounds");
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Index out of bounds");
        return data_[index];
    }

    void push_back(const T& value) {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);

        data_[size_++] = value;
    }

    
    void pop_back() {
        if (size_ == 0)
            throw std::out_of_range("Array is empty");
        --size_;
    }

   
    void insert(std::size_t index, const T& value) {
        if (index > size_)
            throw std::out_of_range("Index out of bounds");

        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);

        for (std::size_t i = size_; i > index; --i)
            data_[i] = data_[i - 1];

        data_[index] = value;
        ++size_;
    }

    
    void erase(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("Index out of bounds");

        for (std::size_t i = index; i < size_ - 1; ++i)
            data_[i] = data_[i + 1];

        --size_;
    }

   
    void clear() {
        size_ = 0;
    }

    
    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_)
            return;

        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = std::move(data_[i]);

        delete[] data_;

        data_ = newData;
        capacity_ = newCapacity;
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

} // namespace dsa
