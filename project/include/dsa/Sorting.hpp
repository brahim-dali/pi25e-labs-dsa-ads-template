//
// Created by marius on 2/19/26.
//

#pragma once
#include <cstddef>

namespace dsa {

    struct SortStats {
        std::size_t comparisons = 0;
        std::size_t swaps = 0;
    };

    template <class T>
    SortStats bubble_sort(T* a, std::size_t n) {
        SortStats st;

        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j + 1 < n - i; ++j) {
                st.comparisons++;

                if (a[j] > a[j + 1]) {
                    T temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    st.swaps++;
                }
            }
        }

        return st;
    }

    template <class T>
    SortStats shell_sort(T* a, std::size_t n) {
        SortStats st;

        for (std::size_t gap = n / 2; gap > 0; gap /= 2) {
            for (std::size_t i = gap; i < n; ++i) {
                T temp = a[i];
                std::size_t j = i;

                while (j >= gap) {
                    st.comparisons++;

                    if (a[j - gap] > temp) {
                        a[j] = a[j - gap];
                        st.swaps++;
                        j -= gap;
                    } else {
                        break;
                    }
                }

                a[j] = temp;
            }
        }

        return st;
    }

} // namespace dsa
