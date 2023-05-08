#pragma once

#ifndef PCMTIMER_ALGORITHM_MODULE_H
#define PCMTIMER_ALGORITHM_MODULE_H

#include <random>
#include "cpucounters.h"

class algorithm_module {
protected:
    algorithm_module() = default;

public:
    ~algorithm_module() = default;

    [[nodiscard]] virtual int
    run(std::uniform_int_distribution<> &dist_small, std::uniform_int_distribution<> &dist_big, std::mt19937 &gen) = 0;
};

#endif //PCMTIMER_ALGORITHM_MODULE_H