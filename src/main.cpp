// Runs one CPU scheduling algorithm on a workload file.
#include "Schedulers.h"
#include <exception>
#include <iostream>
#include <map>
#include <string>

int main(int argc, char** argv) {
    const std::map<std::string, void (*)(const std::vector<ProcessSpec>&)> algorithms = {
        {"fcfs", fcfs::run}, {"sjf", sjf::run}, {"srtf", srtf::run},
        {"rr", rr::run},     {"mlfq", mlfq::run},
    };

    if (argc != 3 || algorithms.count(argv[1]) == 0) {
        std::cerr << "usage: " << argv[0] << " <fcfs|sjf|srtf|rr|mlfq> <workload-file>\n";
        return 1;
    }

    try {
        std::vector<ProcessSpec> processes = loadProcesses(argv[2]);
        algorithms.at(argv[1])(processes);
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
