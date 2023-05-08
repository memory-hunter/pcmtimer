# pcmtimer - Algorithm Runtime Measurer

A template for timing algorithm runtimes, measuring cache hit ratios with [Intel PCM library](https://github.com/intel/pcm/).

The template provides a modular system, there is an algorithm `runner`, which provides timing and random numbers for the algorithms to use and algorithms themselves are provided as `modules`, so from [the main code](https://github.com/memory-hunter/pcmtimer/blob/main/src/pcmtimer.cpp#L24), you can modify what algorithm to run by changing the argument you give to the runner.

The goal of this code is to check if the cache hit ratios are the culprit of having **`out-of-runtime execution times`**, meaning that it is observed that sometimes, for any algorithm, we don't get the expected runtime for an arbitrary n number of elements.

This code is provided as my and my coursemates' bachelor's thesis work at [Kutaisi International University](https://www.kiu.edu.ge/).

# Requirements
- Windows operating system (preferably > 10)
- PC with an Intel CPU (mandatory), since the [Intel PCM library](https://github.com/intel/pcm/) is specialized for Intel's CPUs.

# Installation
- Follow [these instructions](https://github.com/intel/pcm/blob/master/doc/WINDOWS_HOWTO.md) first.
- Clone the repository recursively using the `git clone --recursive` command.
- Open the project using your IDE of choice (which has a way to build using [CMake](https://cmake.org/)).
- Build the project.
- Run the `pcmtimer.exe` from the `{root}/bin/{runtime}/` directory with administrator privilleges.

# Credits
- Mentor: [Wolfgang J. Paul](https://ieeexplore.ieee.org/author/37387171500)
- Students: Davit Petriashvili, Lasha Kvatashidze
