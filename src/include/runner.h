#pragma once

#ifndef PCMTIMER_RUNNER_H
#define PCMTIMER_RUNNER_H

#include <random>
#include <chrono>
#include <fstream>

#include "algorithm_module.h"
#include "printer.h"
#include "cpucounters.h"

class runner {
    std::random_device rd{};
    std::mt19937 gen;
    std::uniform_int_distribution<> small_dis;
    std::uniform_int_distribution<> big_dis;
    std::fstream file{};

    int test_cases{};

public:
    explicit runner(int test_cases);

    runner(int dis_limit, int test_cases);

    runner(int dis_limit_small, int dis_limit_big, int test_cases);

    ~runner();

    void run(algorithm_module *algorithm);
};

#endif //PCMTIMER_RUNNER_H
