#include <filesystem>
#include <memory>
#include <iostream>
#include <cpucounters.h>

#include "runner.cpp"
#include "algorithm_definitions.h"

using pcm::PCM;

void wait() {
    std::cout << "Timing completed. Results are saved in 'test_cases.txt'\n";
    std::cin.get();
}

int main() {

    std::shared_ptr<PCM> m;
    m.reset(PCM::getInstance());
    m->enableForceRTMAbortMode();
    m->checkError(m->program());

    std::unique_ptr<runner> r(new runner(100000, 500));
    r->run(new algorithms::quick_sort());
    r.reset();

    std::filesystem::path cd = std::filesystem::current_path();
    std::filesystem::rename(cd / "test_cases.txt", cd.parent_path().parent_path() / "plot" / "test_cases.txt");

    wait();

}
