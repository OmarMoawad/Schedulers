#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define Q1quantum 8
#define Q2quantum 16
#define idleThreshold 15
struct proc
{
    int pid;
    int arrival;
    int burst;
    int executedCycles;
    int quantumCounter;
    int startTime;
    int idleCounter;
    int finishTime;
    int waitingTime;
    // int leftover;
    // int priority;
};
vector<proc> finishedProcesses;
// To prevent starvation, add a counter that keeps track so that it does not spend a long time in the low priority, goes up in priority as time goes on

bool sortingByArrivalTime(const proc &a, const proc &b)
{
    return a.arrival < b.arrival;
}

int turnaroundTime(vector<proc> finishedProcesses)
{
    int turnaround = 0;
    int sum;
    for (int i = 0; i < finishedProcesses.size(); i++)
    {
        sum = finishedProcesses[i].finishTime - finishedProcesses[i].arrival;
        turnaround = turnaround + sum;
    }
    return turnaround;
}

int waitingTime(vector<proc> finishedProcesses)
{
    int waiting = 0;
    int sum;
    // turnaroundTime(finishedProcesses)
    for (int i = 0; i < finishedProcesses.size(); i++)
    {
        sum = (finishedProcesses[i].finishTime - finishedProcesses[i].arrival) - finishedProcesses[i].burst; // Turnaround - burst
        waiting = sum + waiting;
    }
    return waiting;
}
int responseTime(vector<proc> finishedProcesses)
{
    int response = 0; // startime - arrival
    int sum;
    for (int i = 0; i < finishedProcesses.size(); i++)
    {
        sum = finishedProcesses[i].startTime - finishedProcesses[i].arrival;
        response = sum + response;
    }
    return response;
}
void MLFQ(vector<proc> processes)
{
    int clk = 0;
    sort(processes.begin(), processes.end(), sortingByArrivalTime);

    vector<proc> high, medium, low;

    for (;;)
    {
        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].arrival == clk)
            {
                high.push_back(processes[i]);
                processes.erase(processes.begin() + i);
                i--;
            }
        }

        if (high.size() != 0)
        {
            if (high[0].burst == high[0].executedCycles)
            {
                cout << "ID: " << high[0].pid << endl;
                cout << "started: " << high[0].startTime << endl;
                cout << "Finished: " << (clk - 1) << endl;
                cout << "exec cycles: " << high[0].executedCycles << endl;
                high[0].finishTime = clk - 1;
                finishedProcesses.push_back(high[0]);
                high.erase(high.begin());
            }
            else if (high[0].quantumCounter == Q1quantum)
            {
                clk--;
                high[0].quantumCounter = 0;
                medium.push_back(high[0]);
                high.erase(high.begin());
            }
            else
            {
                if (high[0].startTime == -1)
                    high[0].startTime = clk;
                high[0].executedCycles++;
                high[0].quantumCounter++;
            }
        }

        else if (medium.size() != 0)
        {
            if (medium[0].burst == medium[0].executedCycles)
            {
                cout << "ID: " << medium[0].pid << endl;
                cout << "started: " << medium[0].startTime << endl;
                cout << "Finished: " << (clk - 1) << endl;
                cout << "exec cycles: " << medium[0].executedCycles << endl;
                medium[0].finishTime = clk - 1;
                finishedProcesses.push_back(medium[0]);
                medium.erase(medium.begin());
            }
            else if (medium[0].quantumCounter == Q2quantum)
            {
                clk--;
                medium[0].quantumCounter = 0;
                low.push_back(medium[0]);
                medium.erase(medium.begin());
            }
            else
            {
                medium[0].executedCycles++;
                medium[0].quantumCounter++;
            }
            if (medium.size() > 1)
            {
                for (int i = 1; i < medium.size(); i++)
                {
                    medium[i].idleCounter++;
                    if (medium[i].idleCounter > idleThreshold)
                    {
                        medium[i].waitingTime += medium[i].idleCounter;
                        medium[i].idleCounter = 0;
                        high.push_back(medium[i]);
                        medium.erase(medium.begin() + i);
                        i--;
                    }
                }
            }
        }
        else if (low.size() != 0)
        {
            if (low[0].burst == low[0].executedCycles)
            {
                cout << "ID: " << low[0].pid << endl;
                cout << "started: " << low[0].startTime << endl;
                cout << "Finished: " << (clk - 1) << endl;
                cout << "exec cycles: " << low[0].executedCycles << endl;
                low[0].finishTime = clk - 1;
                finishedProcesses.push_back(low[0]);
                low.erase(low.begin());
            }
            else
            {
                low[0].executedCycles++;
                low[0].quantumCounter++;
            }
            if (low.size() > 1)
            {
                for (int i = 1; i < low.size(); i++)
                {
                    low[i].idleCounter++;
                    if (low[i].idleCounter > idleThreshold)
                    {
                        low[i].waitingTime += low[i].idleCounter;
                        low[i].idleCounter = 0;
                        medium.push_back(low[i]);
                        low.erase(low.begin() + i);
                        i--;
                    }
                }
            }
        }

        if ((high.size() == 0) && (medium.size() == 0) && (low.size() == 0) && (processes.size() == 0))
            break;

        clk++;
    }
}

int main()
{
    vector<proc> processes{
        {0, 0, 15, 0, 0, -1, 0},
        {1, 1, 20, 0, 0, -1, 0},
        {2, 2, 40, 0, 0, -1, 0},
        {3, 3, 43, 0, 0, -1, 0}
        // {1, 1, 8, 0, 0, -1, 0, 0, 0},
        // {2, 1, 30, 0, 0, -1, 0, 0, 0},
        // {3, 1, 9, 0, 0, -1, 0, 0},
    };

    double avgWait, avgResponse, avgTurnaround;
    MLFQ(processes);
    avgWait = waitingTime(finishedProcesses) / double(finishedProcesses.size());
    avgResponse = responseTime(finishedProcesses) / double(finishedProcesses.size());
    avgTurnaround = turnaroundTime(finishedProcesses) / double(finishedProcesses.size());
    cout << "-=======================================================================-" << endl;
    cout << "Average Waiting Time: " << avgWait << endl
         << "Average Response Time: " << avgResponse << endl
         << "Average Turnaround Time: " << avgTurnaround;

    return 0;
}