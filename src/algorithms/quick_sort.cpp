#include "algorithm_module.h"

class quick_sort : public algorithm_module {
    int partition(int *arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void quick_sort_impl(int *arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quick_sort_impl(arr, low, pi - 1);
            quick_sort_impl(arr, pi + 1, high);
        }
    }

public:
    quick_sort() : algorithm_module() {}

    ~quick_sort() = default;

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big,
            std::mt19937 &gen) override {
        int n = dist_big(gen);
        int *arr = new int[n];
        for (int j = 0; j < n; j++)
            arr[j] = dist_big(gen);
        quick_sort_impl(arr, 0, n - 1);
        delete[] arr;
        return n;
    }
};