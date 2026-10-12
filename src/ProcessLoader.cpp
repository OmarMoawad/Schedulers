#include "Schedulers.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<ProcessSpec> loadProcesses(const std::string& path) {
    std::ifstream in(path);
    if (!in)
        throw std::runtime_error("could not open workload file: " + path);

    std::vector<ProcessSpec> processes;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream fields(line);
        ProcessSpec p;
        if (!(fields >> p.pid >> p.arrival >> p.burst))
            throw std::runtime_error("bad line in " + path + ": " + line);
        processes.push_back(p);
    }
    if (processes.empty())
        throw std::runtime_error("no processes found in " + path);
    return processes;
}
