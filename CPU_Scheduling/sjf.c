#include <stdio.h>
#include <stdbool.h>

struct process {
    int pid;       
    int at;        
    int bt;        
    int ct;       
    int tat;       
    int wt;        
    int completed; 
} pro[20];

// Function to perform SJF Non-preemptive scheduling
void calculate(int n) {
    int completedCount = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;
    int execOrder[20], k = 0;
    for(int i=0;i<n;i++)
    {
        pro[i].completed=0;
    }
    while (completedCount < n) {
        int idx = -1;
        int minBT = 9999;

        // Find process with smallest burst time among arrived & not completed
        for (int i = 0; i < n; i++) {
            if (!pro[i].completed && pro[i].at <= currentTime) {
                if (pro[i].bt < minBT) {
                    minBT = pro[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {  // If process is yet to arrive increase count 
            currentTime++;
            continue;
        }

        // Execute selected process
        pro[idx].ct = currentTime + pro[idx].bt;
        pro[idx].tat = pro[idx].ct - pro[idx].at;
        pro[idx].wt = pro[idx].tat - pro[idx].bt;

        totalTAT += pro[idx].tat;
        totalWT += pro[idx].wt;

        currentTime = pro[idx].ct;
        pro[idx].completed = 1;

        execOrder[k++] = idx; // Save order for Gantt chart
        completedCount++;
    }

    // Display results
    printf("\nSJF (Non-preemptive) Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pro[i].pid, pro[i].at, pro[i].bt, pro[i].ct, pro[i].tat, pro[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time : %.2f\n", totalWT / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < k; i++) {
        printf(" P%d |", pro[execOrder[i]].pid);
    }
    printf("\n0");
    for (int i = 0; i < k; i++) {
        printf(" %d", pro[execOrder[i]].ct);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pro[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", i + 1);
        scanf("%d", &pro[i].at);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &pro[i].bt);
        pro[i].completed = false;
    }

    calculate(n);
    return 0;
}
