#include <bits/stdc++.h>
using namespace std;

//structure for every process
struct Process {
   int pid; // Process ID
   int art; // Arrival Time
   int bt; // Burst Time
   int rdy=0;
};


void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
   for (int i = 0; i < n; i++)
   tat[i] = proc[i].bt + wt[i];
}
class Node
{
    public:
    Process prc;
    Node* next=NULL; 
};
Node* head = NULL;
void INSERT(Process prc){
        Node * new_node = new Node();
        (new_node->prc)=prc;
        new_node->next=NULL;
        Node* tmp=head; 
        if(head==NULL){head=new_node;}
        else{while(tmp->next!=NULL){
                tmp=tmp->next;                
        }
        tmp->next=new_node;}        
}
void print(){
        if(head==NULL){cout<<"qNULLq";}
        else{Node *tmp;
        cout<<"q"<<head->prc.pid<<"q";if(head->next!=NULL){tmp=head->next;}
            while(tmp!=NULL){
            cout<<"q"<<tmp->prc.pid<<"q";tmp=tmp->next;         
            }        
        }cout<<endl;
}
//waiting time of all process
void findWaitingTime(Process proc[], int n, int wt[], int RT[], int FT[], int GantChart[], int t[], int UT[], int CT[], int TQ[]) {
      
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
         if ((proc[j].art <= t[0]) && rt[j] > 0 && proc[j].rdy==0) {proc[j].rdy=1;INSERT(proc[j]);}
      }
      if(head!=NULL){check=true;}else{check=false;}
      if (check == false && head==NULL) {
         GantChart[t[0]]=0;UT[0]++;
         t[0]++;
         continue;
      }
      // decrementing the remaining time. 
      if(firstpt[((head->prc.pid))-1]==-1){
      firstpt[((head->prc.pid))-1]=t[0];
      RT[((head->prc.pid))-1]=firstpt[((head->prc.pid))-1]-proc[((head->prc.pid))-1].art;
      if(RT[((head->prc.pid))-1]<0){RT[((head->prc.pid))-1]=0;}
      }
      if(rt[((head->prc.pid))-1]<TQ[0]){
      for(int ijk=0;ijk<rt[((head->prc.pid))-1];ijk++){
      for (int j = 0; j < n; j++) {
         if ((proc[j].art <= t[0]+1) && rt[j] > 0 && proc[j].rdy==0) {proc[j].rdy=1;INSERT(proc[j]);}
      }    
            GantChart[t[0]]=proc[((head->prc.pid))-1].pid;t[0]++;
            rt[((head->prc.pid))-1]--;
                
        }
      }
        else{
        for(int ijk=0;ijk<TQ[0];ijk++){
            for (int j = 0; j < n; j++) {
         if ((proc[j].art <= t[0]+1) && rt[j] > 0 && proc[j].rdy==0) {proc[j].rdy=1;INSERT(proc[j]);}
            }      
        GantChart[t[0]]=proc[((head->prc.pid))-1].pid;t[0]++;rt[((head->prc.pid))-1]--;}
        }
      FT[0]=t[0];
         // If a process gets completely
         // executed
         if (rt[((head->prc.pid))-1] == 0){
            complete++;
            finish_time = t[0];
            CT[((head->prc.pid))-1]=finish_time;
            // Calculate waiting time
            wt[((head->prc.pid))-1] = finish_time -
            proc[((head->prc.pid))-1].bt -
            proc[((head->prc.pid))-1].art;
            if (wt[((head->prc.pid))-1] < 0)
               wt[((head->prc.pid))-1] = 0;
        head=(head->next);

        }
        else{
            Process prc1=head->prc;head=(head->next);INSERT(prc1);
        }
   }
}

// Function to calculate average time

void findavgTime(Process proc[], int n) {
   int TQ[1];TQ[0]=2;//Time Quantum
   int wt[n], tat[n], RT[n], total_wt = 0, UT[1],
   total_tat = 0, total_RT = 0, FT[1], t[1], CT[n];
   int GantChart[99999];t[0]=0;UT[0]=0;
   // Function to find waiting time of all
   // processes
   findWaitingTime(proc, n, wt, RT, FT, GantChart, t, UT, CT, TQ);
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
   Process proc[] = { { 1, 0, 5 }, { 2, 1, 4 }, { 3, 2, 2 }, { 4, 4, 1 } };
   int n = sizeof(proc) / sizeof(proc[0]);
   findavgTime(proc, n);
   return 0;
}
