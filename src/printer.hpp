#pragma once

#ifndef PRINTER_H
#define PRINTER_H
#include <iostream>
#include <cpucounters.h>

namespace printer
{
    void printSystemCounterStateDiff(const pcm::SystemCounterState &before, const pcm::SystemCounterState &after)
    {
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

    void log(int n, std::chrono::nanoseconds duration, const pcm::SystemCounterState &before, const pcm::SystemCounterState &after)
    {
        std::cout << "Runtime: " << duration.count() << ", n: " << n << ", L2 ratio: " << getL2CacheHitRatio(before, after) << ", L3 ratio: " << getL3CacheHitRatio(before, after) << "\n";
    }

    void log(int n, std::chrono::nanoseconds duration, const pcm::SystemCounterState &before, const pcm::SystemCounterState &after, std::fstream &file){
        file << n << " " << duration.count() << " " << getL2CacheHitRatio(before, after) << " " << getL3CacheHitRatio(before, after) << "\n";
    }
}

#endif