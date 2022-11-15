#include "example.cpp"

void wait() {
    std::cout << "Press any key to continue... " << std::endl << std::flush;
    std::cin.ignore(INT32_MAX, '\n');
}

int main() {
    example_algorithm *ea = new example_algorithm();

    std::cout << "Starting example algorithm...\n";

    ea->run();

    std::cout << "Example algorithm finished.\n";

    wait();

    delete ea;
}
