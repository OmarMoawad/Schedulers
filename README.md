# CPU Schedulers

A C++ simulator for five CPU scheduling algorithms that operating systems use. It reads a
workload of processes from a file and runs the chosen algorithm on it. It then prints each
process's waiting, turnaround, response and completion times, plus the averages.

| Algorithm | Key    | Notes                                                              |
|-----------|--------|--------------------------------------------------------------------|
| First-Come First-Served      | `fcfs` | non-preemptive; prints a Gantt chart                 |
| Shortest Job First           | `sjf`  | non-preemptive; prints a Gantt chart                 |
| Shortest Remaining Time First| `srtf` | preemptive SJF; prints a Gantt chart                 |
| Round Robin                  | `rr`   | time quantum = 2; prints a Gantt chart               |
| Multi-Level Feedback Queue   | `mlfq` | 3 queues (quantum 8, quantum 16, FCFS) with aging after 15 idle cycles to prevent starvation |

`#C++` `#Operating_Systems` `#CPU_Scheduling`

## Project structure

```
Schedulers/
├── src/
│   ├── main.cpp            # command-line entry point: picks the algorithm, loads the workload
│   ├── Schedulers.h        # ProcessSpec type and the run() function of each scheduler
│   ├── ProcessLoader.cpp   # reads a workload file from data/
│   └── schedulers/         # one file per algorithm (FCFS, SJF, SRTF, RR, MLFQ)
├── data/                   # example workloads, one per algorithm
├── Makefile
└── README.md
```

## Requirements

- A C++17 compiler (`g++` or `clang++`)
- `make`

There are no external libraries.

## Build

```bash
make
```

This produces the executable `build/schedulers`.

## Usage

```bash
./build/schedulers <fcfs|sjf|srtf|rr|mlfq> <workload-file>
```

### Workload file format

The file has one process per line: `pid arrival_time burst_time`. Lines that start with `#`
are comments.

```
# pid arrival burst
1 0 2
2 1 2
3 5 3
4 6 4
```

For `fcfs`, `sjf`, `srtf` and `rr`, number the process ids `1..n` in order. The
`data/mlfq_example.txt` workload numbers them from `0`, as the original MLFQ test did.

### Example

```bash
./build/schedulers fcfs data/fcfs_example.txt
```

```
Processes  Arrival time  Burst time  Waiting time  Turnaround time  Response Time  Completion Time
 1		0		2		 0		 2		 0		 2
 2		1		2		 1		 3		 1		 4
 3		5		3		 0		 3		 0		 8
 4		6		4		 2		 6		 2		 12
GantChart:1-1-2-2-0-3-3-3-4-4-4-4

Average waiting time = 0.75
Average turn around time = 3.5
Average Response Time = 0.75
Throughput = 0.333333
Utilization = 0.916667
```

In the Gantt chart, `0` means the CPU was idle during that time unit.

To run every algorithm on its example workload:

```bash
make demo
```
