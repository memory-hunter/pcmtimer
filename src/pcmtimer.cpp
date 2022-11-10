#include "example.cpp"

void wait() {
    std::cout << "Press any key to continue... " << std::endl << std::flush;
    std::cin.ignore(INT32_MAX, '\n');
}

int main() {
    // pcm::PCM *m = pcm::PCM::getInstance();

    // if (m->program() != pcm::PCM::Success)
    //     return -1;

    example_algorithm *ea = new example_algorithm();

    std::cout << "Starting example algorithm...\n";

    //pcm::SystemCounterState before = pcm::getSystemCounterState();
    ea->run();
    // pcm::SystemCounterState after = pcm::getSystemCounterState();

    std::cout << "Example algorithm finished.\n";
    //printer::printSystemCounterStateDiff(before, after);

    wait();

    delete ea;
}
