#include "runner.h"

runner::runner(int test_cases) : runner(100, 100000, test_cases) {}

runner::runner(int dis_limit, int test_cases) : runner(dis_limit, dis_limit, test_cases) {}

runner::runner(int dis_limit_small, int dis_limit_big, int test_cases) : test_cases(test_cases) {
    gen = std::mt19937(rd());
    small_dis = std::uniform_int_distribution<>(0, dis_limit_small);
    big_dis = std::uniform_int_distribution<>(0, dis_limit_big);
    file = std::fstream("test_cases.txt", std::ios::out);
}

void runner::run(algorithm_module *algorithm) {
    pcm::SystemCounterState before_state = pcm::getSystemCounterState();
    for (int i = 0; i < test_cases; ++i) {
        algorithm->setup(small_dis, big_dis, gen);
        auto start = std::chrono::high_resolution_clock::now();
        int returned_n = algorithm->run(small_dis, big_dis, gen);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<octosecond>(end - start);
        SystemCounterState after_state = pcm::getSystemCounterState();
        printer::log_stdout(i, returned_n, duration, before_state, after_state);
        printer::log_file(returned_n, duration, before_state, after_state, file);
    }
}

runner::~runner() {
    file.close();
}
