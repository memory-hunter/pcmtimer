#pragma once

#ifndef PCMTIMER_PRINTER_H
#define PCMTIMER_PRINTER_H

#include <iostream>
#include <chrono>
#include <cpucounters.h>

using pcm::SystemCounterState;

namespace printer {
    void print_difference(const SystemCounterState &before, const SystemCounterState &after) {
        std::cout << "Instructions per Clock: " << getIPC(before, after)
                  << "\nL2 cache hits: " << getL2CacheHits(before, after)
                  << "\nL2 cache misses: " << getL2CacheMisses(before, after)
                  << "\nL2 cache hit ratio: " << getL2CacheHitRatio(before, after)
                  << "\nL3 cache hits: " << getL3CacheHits(before, after)
                  << "\nL3 cache misses: " << getL3CacheMisses(before, after)
                  << "\nL3 cache hit ratio: " << getL3CacheHitRatio(before, after)
                  << "\nBytes read from DRAM: " << getBytesReadFromMC(before, after)
                  << "\n";
    }

    template <typename time_unit>
    void log_stdout(int i, int n, time_unit duration, const SystemCounterState &before, const SystemCounterState &after) {
        std::cout << "Iteration: " << i << ", n: " << n << ", Runtime: " << duration.count() << ", L2 ratio: "
                  << getL2CacheHitRatio(before, after) << ", L3 ratio: " << getL3CacheHitRatio(before, after) << "\n";
    }

    template <typename time_unit>
    void log_file(int n, time_unit duration, const SystemCounterState &before, const SystemCounterState &after,
                  std::fstream &file) {
        file << n << " " << duration.count() << " " << getL2CacheHitRatio(before, after) << " "
             << getL3CacheHitRatio(before, after) << "\n";
    }
}

#endif //PCMTIMER_PRINTER_H