#include<stdio.h>
struct process{
 int pid;
 int at;
 int bt;
 int tat;
 int ct;
 int wt;
}pro[20];
void calculate(int n){
 int i,c=0;
 //c is to track arrival time and account for any buffers between arrival times and completion times//
 for(i=0;i<n;i++){
 if(c<pro[i].at)
 {
 c=pro[i].at;
 }
 pro[i].ct=c+pro[i].bt;
 pro[i].tat= pro[i].ct-pro[i].at;
 pro[i].wt=pro[i].tat-pro[i].bt;
 c=pro[i].ct;
 }
}
void gantt(int n){
 printf("FCFS:\n");
 printf("\nGANTT CHART:\n");
 printf("|");
 for(int i=0;i<n;i++){
 printf(" P%d | ",pro[i].pid);
 }printf("\n0 ");
 for (int i = 0; i < n; i++) {
 printf(" %d ", pro[i].ct);
 }
}
void display(int n){
 float t=0,w=0;
 int i;
 printf("\n");
 printf("process name\tarrival time\tburst time\tcompletion time\ttat\t wt\n");
 for(i=0;i<n;i++){
 
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].
ct,pro[i].tat,pro[i].wt);
 t=t+pro[i].tat;
 w=w+pro[i].wt;
 }
 printf("average turn around time=%f\n",t/n);
 printf("average waiting time=%f\n",w/n);
}
int main(){
 int n;
 printf("enter the number of processes:");
 scanf("%d",&n);
 int i,j;
 struct process temp;
 for(i=0;i<n;i++){
 printf("enter the arrival time of process %d:",i+1);
 scanf("%d",&pro[i].at);
 printf("enter the burst time of process %d:",i+1);
 scanf("%d",&pro[i].bt);
 pro[i].pid=i+1;
 }
 for(i=0;i<n-1;i++){
 for(j=0;j<n-i-1;j++){
 if(pro[j].at>pro[j+1].at||
(pro[j].at==pro[j+1].at&&pro[j].pid>pro[j+1].pid)){
 temp=pro[j];
 pro[j]=pro[j+1];
 pro[j+1]=temp;
 }
 }
 }
 calculate(n);
 gantt(n);
 display(n);
}
