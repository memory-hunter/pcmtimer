#include "algorithm_container.hpp"
#include "printer.hpp"

class quick_sort : public algorithm_container
{
    public:
        quick_sort() = default;
        ~quick_sort() = default;

        inline int partition(int* arr, int low, int high)
        {
            int pivot = arr[high];
            int i = low - 1;
            for (int j = low; j < high; j++) {
                if (arr[j] < pivot)
                {
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }
            std::swap(arr[i + 1], arr[high]);
            return i + 1;
        }

        inline void quick_sort_impl(int* arr, int low, int high)
        {
            if (low < high)
            {
                int pi = partition(arr, low, high);
                quick_sort_impl(arr, low, pi - 1);
                quick_sort_impl(arr, pi + 1, high);
            }
        }

        void run() override
        {
            pcm::PCM *m = pcm::PCM::getInstance();
            // srand(time(nullptr));
            std::fstream file("quick_test_cases.txt", std::ios::out);
            for (int k = 0; k < 1000; k++)
            {
                int n = rand() % 1000000;
                int* arr = new int[n];
                for (int k = 0; k < n; k++)
                    arr[k] = rand() % INT_MAX;
                pcm::SystemCounterState before_state = pcm::getSystemCounterState();
                auto start = std::chrono::high_resolution_clock::now();
                quick_sort_impl(arr, 0, n - 1);
                auto end = std::chrono::high_resolution_clock::now();
                pcm::SystemCounterState after_state = pcm::getSystemCounterState();
                std::chrono::nanoseconds duration = end - start;
                /*
                if (duration.count() / n / log(n) > 28){
                    printer::printSystemCounterStateDiff(before_state, after_state);
                }  */
                if (duration.count() / n / log(n) < 13 && n > 20000){
                    printer::printSystemCounterStateDiff(before_state, after_state);
                }
                file << n << " " << duration.count() << "\n";
                delete arr;
            }
            file.close();
        }
};