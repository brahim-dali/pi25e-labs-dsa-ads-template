#pragma once
#include "DynamicArray.hpp"
#include <stdexcept>

namespace dsa {

template <class T>
class Stack {
public:
    Stack() = default;

    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (empty()) throw std::out_of_range("Stack is empty");
        data_.pop_back();
    }

    T& top() {
        if (empty()) throw std::out_of_range("Stack is empty");
        return data_.at(data_.size() - 1);
    }

    const T& top() const {
        if (empty()) throw std::out_of_range("Stack is empty");
        return data_.at(data_.size() - 1);
    }

    bool empty() const { return data_.size() == 0; }

    std::size_t size() const { return data_.size(); }

private:
    DynamicArray<T> data_;
};

} // namespace dsa
