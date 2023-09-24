#include "algorithm_module.h"

class bubble_sort : public algorithm_module {

    void bubble_sort_impl(int arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    int n{};
    int *arr;

public:
    bubble_sort() : algorithm_module() {}

    ~bubble_sort() {
        delete[] arr;
    }

    int run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        bubble_sort_impl(arr, n);
        return n;
    }

    void setup(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) override {
        n = dist_big(gen);
        arr = new int[n];
        for (int j = 0; j < n; j++)
            arr[j] = dist_big(gen);
    }
};