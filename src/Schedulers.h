#pragma once
#include <string>
#include <vector>

// One process in a workload file: id, arrival time and CPU burst time.
struct ProcessSpec {
    int pid;
    int arrival;
    int burst;
};

// Reads "pid arrival burst" lines from a workload file. Blank lines and lines
// starting with '#' are skipped.
std::vector<ProcessSpec> loadProcesses(const std::string& path);

// Each scheduler prints its per-process table and the averages to stdout.
namespace fcfs { void run(const std::vector<ProcessSpec>& processes); } // First-Come First-Served
namespace sjf  { void run(const std::vector<ProcessSpec>& processes); } // Shortest Job First
namespace srtf { void run(const std::vector<ProcessSpec>& processes); } // Shortest Remaining Time First
namespace rr   { void run(const std::vector<ProcessSpec>& processes); } // Round Robin, quantum 2
namespace mlfq { void run(const std::vector<ProcessSpec>& processes); } // Multi-Level Feedback Queue
