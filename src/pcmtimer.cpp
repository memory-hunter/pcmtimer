#include "algorithm_container.hpp"
#include "example.cpp"
#include "printer.hpp"

void wait() {
    std::cout << "Press any key to continue... " << std::endl << std::flush;
    std::cin.ignore(INT32_MAX, '\n');
}

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

    wait();

    delete ea;
}