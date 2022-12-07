#include "quicksort.cpp"
#include "bubblesort.cpp"
#include "avl.cpp"

#include <filesystem>

void wait() {
    std::cout << "Press any key to continue... " << std::endl;
    std::cin.ignore(LLONG_MAX, '\n');
}

int main() {

    pcm::PCM *m = pcm::PCM::getInstance();
    m->enableForceRTMAbortMode();
    m->checkError(m->program());

    avl_tree* algo = new avl_tree();
    algo->run();

    std::filesystem::path cd = std::filesystem::current_path();
    std::filesystem::rename(cd / "test_cases.txt", cd.parent_path().parent_path() / "src" / "plot" / "test_cases.txt");
    // std::filesystem::rename(cd / "good_runs.txt", cd.parent_path().parent_path() / "src" / "plot" / "good_runs.txt");
    // std::filesystem::rename(cd / "bad_runs.txt", cd.parent_path().parent_path() / "src" / "plot" / "bad_runs.txt");

    wait();

    delete algo;
    delete m;
}
