#include "algorithm_container.hpp"
#include "printer.hpp"

class bubble_sort : public algorithm_container
{
    public:
        bubble_sort() = default;
        ~bubble_sort() = default;
        void run() override
        {
            pcm::PCM *m = pcm::PCM::getInstance();
            std::fstream file("bubble_test_cases_included_pcm.txt", std::ios::out);
            for (int k = 0; k < 1000; k++)
            {
                int n = rand() % 1000000;
                int* arr = new int[n];
                for (int k = 0; k < n; k++)
                    arr[k] = rand() % INT_MAX;
                pcm::SystemCounterState before_state = pcm::getSystemCounterState();
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < n - 1; i++)
                    for (int j = 0; j < n - i - 1; j++)
                        if (arr[j] > arr[j + 1])
                            std::swap(arr[j], arr[j + 1]);
                auto end = std::chrono::high_resolution_clock::now();
                pcm::SystemCounterState after_state = pcm::getSystemCounterState();
                std::chrono::nanoseconds duration = end - start;
                /*
                if ((float(float(duration.count()) / n) / n) > 1.69 ){
                    printer::printSystemCounterStateDiff(before_state, after_state);
                } */
                if ((float(float(duration.count()) / n) / n) < 1.69){
                    printer::printSystemCounterStateDiff(before_state, after_state);
                }
                file << n << " " << duration.count() << "\n";
                delete arr;
            }
            file.close();
        }
};