#include <cpucounters.h>

#include "algorithm_container.cpp"
#include "printer.cpp"

int main() {

    pcm::PCM* m = pcm::PCM::getInstance();

    if (m->program() != pcm::PCM::Success) return -1;

    algorithm_container container;

    pcm::SystemCounterState before = pcm::getSystemCounterState();
    container.run();
    pcm::SystemCounterState after = pcm::getSystemCounterState();

    printer::printSystemCounterStateDiff(before, after);
}