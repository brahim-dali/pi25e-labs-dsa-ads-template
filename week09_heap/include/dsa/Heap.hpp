//
// Created by marius on 2/19/26.
//

#pragma once
#include <cstddef>
#include <stdexcept>
#include "dsa/DynamicArray.hpp"

namespace dsa {

    template <class T>
    class Heap {
    public:
        Heap() = default;

        bool empty() const { return data_.size() == 0; }
        std::size_t size() const { return data_.size(); }

        const T& top() const {
            if (empty()) throw std::out_of_range("Heap::top on empty heap");
            return data_[0];
        }

        void push(const T& value) {
            data_.push_back(value);
            sift_up(data_.size() - 1);
        }

        void pop() {
            if (empty()) {
                throw std::out_of_range("Heap::pop on empty heap");
            }

            data_[0] = data_[data_.size() - 1];
            data_.pop_back();

            if (!empty()) {
                sift_down(0);
            }
        }

    private:
        static std::size_t parent(std::size_t i) { return (i - 1) / 2; }
        static std::size_t left(std::size_t i) { return 2 * i + 1; }
        static std::size_t right(std::size_t i) { return 2 * i + 2; }

        void sift_up(std::size_t i) {
            while (i > 0 && data_[parent(i)] < data_[i]) {
                T temp = data_[i];
                data_[i] = data_[parent(i)];
                data_[parent(i)] = temp;

                i = parent(i);
            }
        }

        void sift_down(std::size_t i) {
            while (true) {
                std::size_t largest = i;
                std::size_t l = left(i);
                std::size_t r = right(i);

                if (l < data_.size() && data_[l] > data_[largest]) {
                    largest = l;
                }

                if (r < data_.size() && data_[r] > data_[largest]) {
                    largest = r;
                }

                if (largest == i) {
                    break;
                }

                T temp = data_[i];
                data_[i] = data_[largest];
                data_[largest] = temp;

                i = largest;
            }
        }

    private:
        DynamicArray<T> data_;
    };

} // namespace dsa
