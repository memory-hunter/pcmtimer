#pragma once

#ifndef PCMTIMER_TIME_UNITS_H
#define PCMTIMER_TIME_UNITS_H

#include <chrono>

using octosecond = std::chrono::duration<long long, std::ratio<1, 100000000>>;

#endif //PCMTIMER_TIME_UNITS_H
