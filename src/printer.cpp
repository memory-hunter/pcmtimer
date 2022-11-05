#ifndef PRINTER_H
#define PRINTER_H
#include <iostream>
#include <cpucounters.h>
#endif

namespace printer {
    void printSystemCounterStateDiff(const pcm::SystemCounterState &before, const pcm::SystemCounterState &after){
        std::cout << "Instructions per Clock: " << getIPC(before, after) <<
         "\nL2 cache hits: " << getL2CacheHits(before, after) <<
         "\nL2 cache misses: " << getL2CacheMisses(before, after) <<
         "\nL2 cache hit ratio: " << getL2CacheHitRatio(before, after) <<
         "\nL3 cache hits: " << getL3CacheHits(before, after) <<
         "\nL3 cache misses: " << getL3CacheMisses(before, after) <<
         "\nL3 cache hit ratio: " << getL3CacheHitRatio(before, after) <<
         "\nBytes read from DRAM: " << getBytesReadFromMC(before, after) << std::endl;
    }
}