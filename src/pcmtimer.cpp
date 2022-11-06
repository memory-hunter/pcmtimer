#include "algorithm_container.hpp"
#include "example.cpp"
#include "printer.hpp"

int main()
{
    pcm::PCM *m = pcm::PCM::getInstance();

    if (m->program() != pcm::PCM::Success)
        return -1;

    example_algorithm *ea = new example_algorithm();

    pcm::SystemCounterState before = pcm::getSystemCounterState();
    ea->run();
    pcm::SystemCounterState after = pcm::getSystemCounterState();

    printer::printSystemCounterStateDiff(before, after);

    delete ea;
}