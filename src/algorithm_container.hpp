#pragma once

#ifndef ALGORITHM_CONTAINER_H
#define ALGORITHM_CONTAINER_H
#include <vector>
#include <random>
#include <chrono>
#include <cpucounters.h>

#include "printer.hpp"

class algorithm_container {
protected:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> small_dis;
    std::uniform_int_distribution<> big_dis;
    algorithm_container() {
        gen = std::mt19937(rd());
        small_dis = std::uniform_int_distribution<>(0, 10);
        big_dis = std::uniform_int_distribution<>(0, 1000000);
    }
public:
    ~algorithm_container() = default;
    virtual void run() = 0;
    virtual int complexity_function(uint64_t x){
        return 0;
    }
    virtual bool is_bad_run(uint64_t n, uint64_t runtime) {
        return false;
    }
};

#endif