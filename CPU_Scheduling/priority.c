#include <stdio.h>
#include <stdbool.h>

struct process {
    int pid;     
    int at;    
    int bt;         
    int pr;         
    int ct;         
    int tat;        
    int wt;         
    int completed;  
} pro[20];

// Function to perform Priority Scheduling (Non-preemptive)
void calculate(int n) {
    int completedCount = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;
    int execOrder[20], k = 0;

    for (int i = 0; i < n; i++) {
        pro[i].completed = 0;
    }

    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 9999;

        // Find process with highest priority among arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!pro[i].completed && pro[i].at <= currentTime) {
                if (pro[i].pr < highestPriority) {
                    highestPriority = pro[i].pr;
                    idx = i;
                }
                // If priorities are equal, choose the one that arrived earlier
                else if (pro[i].pr == highestPriority) {
                    if (idx == -1 || pro[i].at < pro[idx].at)
                        idx = i;
                }
            }
        }

        if (idx == -1) { // No process has arrived yet
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
    printf("\nPriority Scheduling (Non-preemptive):\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pro[i].pid, pro[i].at, pro[i].bt, pro[i].pr,
               pro[i].ct, pro[i].tat, pro[i].wt);
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
        printf("Enter Priority for P%d (smaller = higher priority): ", i + 1);
        scanf("%d", &pro[i].pr);
        pro[i].completed = false;
    }

    calculate(n);
    return 0;
}
