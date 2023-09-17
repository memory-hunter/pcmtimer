#include <filesystem>
#include <memory>
#include <iostream>
#include <cpucounters.h>

#include "runner.h"

#include "avl_trees.cpp"
#include "quick_sort.cpp"
#include "dijsktra.cpp"
#include "lca.cpp"

using pcm::PCM;

int main() {

    std::shared_ptr<PCM> m;
    m.reset(PCM::getInstance());
    m->enableForceRTMAbortMode();
    m->checkError(m->program());

    std::unique_ptr<runner> r(new runner(100000, 5));
    r->run(new lca());
    r.reset();

    std::filesystem::path cd = std::filesystem::current_path();
    std::filesystem::rename(cd / "test_cases.txt", cd.parent_path().parent_path() / "plot" / "test_cases.txt");
}
