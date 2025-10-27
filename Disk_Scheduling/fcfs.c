#include <stdio.h>
#include <stdlib.h>
void FCFS(int requests[], int n, int head)
{
    int totalHeadMovement = 0;
    printf("\nSeek Sequence (FCFS): ");
    for (int i = 0; i < n; i++)
    {
        printf("%d -> ", requests[i]);
        totalHeadMovement += abs(requests[i] - head);
        head = requests[i];
    }
    printf("END\n");
    printf("Total Head Movement = %d\n", totalHeadMovement);    
}

int main()
{
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    FCFS(requests, n, head);
    return 0;
}

/*request that came first is processed first,each request is taken and the dist btwn it and the current head is calculated, then the head moves to the current request beign processed and this continues till all requests have been processed*/