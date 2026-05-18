//
// Created by marius on 2/19/26.
//

#pragma once
#include <cstddef>

namespace dsa {

    template <class T>
    void heapify_down(T* arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            T temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            heapify_down(arr, n, largest);
        }
    }

    template <class T>
    void build_heap(T* arr, int n) {
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify_down(arr, n, i);
        }
    }

    template <class T>
    void heapsort(T* arr, int n) {
        build_heap(arr, n);

        for (int i = n - 1; i > 0; --i) {
            T temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            heapify_down(arr, i, 0);
        }
    }

} // namespace dsa
