#include <bits/stdc++.h>
using namespace std;

//structure for every process
struct Process {
   int pid; // Process ID
   int art; // Arrival Time
   int bt; // Burst Time
};


void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
   for (int i = 0; i < n; i++)
   tat[i] = proc[i].bt + wt[i];
}

//waiting time of all process
void findWaitingTime(Process proc[], int n, int wt[], int RT[], int FT[], int GantChart[], int t[], int UT[], int CT[]) {

   
   int rt[n];
   int firstpt[n];int min_pid;
   for(int i=0;i<n;i++){firstpt[i]=-1;}
   for (int i = 0; i < n; i++)
   rt[i] = proc[i].bt;
   int complete = 0, min=INT_MAX;
   int shortest = 0, finish_time;
   bool check = false;
   while (complete != n) {
      for (int j = 0; j < n; j++) {
         if ((proc[j].art <= t[0]) && rt[j] > 0 && rt[j] <= min) {
         //the following condition is to prioritize processes with similar burst time but with an earlier pid            
            if(rt[j]==min && proc[j].pid<min_pid){min_pid = proc[j].pid;shortest = j;check=true;}
            else if(rt[j]<min){min = rt[j];min_pid = proc[j].pid;
            shortest = j;
            check = true;}
         }
      }
      if (check == false) {
         GantChart[t[0]]=0;UT[0]++;
         t[0]++;
         continue;
      }
      // decrementing the remaining time
      int asdf=rt[shortest];rt[shortest]=0;
      if(firstpt[shortest]==-1){firstpt[shortest]=t[0];RT[shortest]=firstpt[shortest]-proc[shortest].art;if(RT[shortest]<0){RT[shortest]=0;}}
      for(int i=0;i<asdf;i++){
            GantChart[t[0]]=proc[shortest].pid;t[0]++;
        }FT[0]=t[0];
         // If a process gets completely
         // executed
         if (rt[shortest] == 0) {
            min = INT_MAX;
            complete++;
            check = false;
            finish_time = t[0];
            CT[shortest]=finish_time;
            // Calculate waiting time
            wt[shortest] = finish_time -
            proc[shortest].bt -
            proc[shortest].art;
            if (wt[shortest] < 0)
               wt[shortest] = 0;
         }
   }
}

// Function to calculate average time

void findavgTime(Process proc[], int n) {
   int wt[n], tat[n], RT[n], total_wt = 0, UT[1],
   total_tat = 0, total_RT = 0, FT[1], t[1], CT[n];
   int GantChart[99999];t[0]=0;UT[0]=0;
   // Function to find waiting time of all
   // processes
   findWaitingTime(proc, n, wt, RT, FT, GantChart, t, UT, CT);
   // Function to find turn around time for
   // all processes
   findTurnAroundTime(proc, n, wt, tat);
   cout << "Processes " << " Arrival time " << " Burst time " << " Waiting time " << " Turnaround time " << " Response Time " << " Completion Time\n";
   for (int i = 0; i < n; i++) {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      total_RT = total_RT + RT[i];
      cout << " " << proc[i].pid << "\t\t" << proc[i].art << "\t\t" << proc[i].bt << "\t\t " << wt[i] << "\t\t " << tat[i] <<  "\t\t " << RT[i] << "\t\t " << CT[i] << endl;
   }cout<<"GantChart:"<<GantChart[0];
   for(int i=1;i<t[0];i++){
    cout<<"-"<<GantChart[i];
    }cout<<endl;
   cout << "\nAverage waiting time = " << (float)total_wt / (float)n; cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
   cout << "\nAverage Response Time = " << (float)total_RT / (float)n; cout << "\nThroughput = " << (float)n / (float)FT[0];
   cout << "\nUtilization = " << (float)(FT[0]-UT[0]) / (float)FT[0]<<"\n";
}

// main function
int main() {
   Process proc[] = { { 1, 1, 3 }, { 2, 2, 4 }, { 3, 1, 2 }, { 4, 4, 4 } };
   int n = sizeof(proc) / sizeof(proc[0]);
   findavgTime(proc, n);
   return 0;
}
