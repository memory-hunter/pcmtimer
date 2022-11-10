#pragma once

#ifndef ALGORITHM_CONTAINER_H
#define ALGORITHM_CONTAINER_H
#include <bits/stdc++.h>
#include <chrono>
#include <cpucounters.h>

#include "printer.hpp"

class algorithm_container {
protected:
    algorithm_container() = default;
public:
    ~algorithm_container() = default;
    virtual void run() = 0;
};

#endif