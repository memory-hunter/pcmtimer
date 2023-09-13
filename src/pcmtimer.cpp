#include <filesystem>
#include <memory>
#include <iostream>
#include <cpucounters.h>

#include "runner.h"

#include "avl_trees.cpp"
#include "quick_sort.cpp"
#include "dijsktra.cpp"

using pcm::PCM;

int main() {

    std::shared_ptr<PCM> m;
    m.reset(PCM::getInstance());
    m->enableForceRTMAbortMode();
    m->checkError(m->program());

    std::unique_ptr<runner> r(new runner(100000, 500));
    r->run(new dijkstra());
    r.reset();

    std::filesystem::path cd = std::filesystem::current_path();
    std::filesystem::rename(cd / "test_cases.txt", cd.parent_path().parent_path() / "plot" / "test_cases.txt");
}
