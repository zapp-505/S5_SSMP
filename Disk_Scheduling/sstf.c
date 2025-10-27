// Chooses the request closest to the current head position.
#include <stdio.h>
#include <stdlib.h>
void SSTF(int requests[], int n, int head)
{
    int completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }
    int totalHeadMovement = 0, completedCount = 0;
    printf("\nSeek Sequence (SSTF): ");
    while (completedCount < n)
    {
        int minDist = 99999;
        int idx = -1;
        // to check for the request nearest to head
        for (int i = 0; i < n; i++)
        {
            if (!completed[i])
            {
                int dist = abs(requests[i] - head);
                if (dist < minDist)
                {
                    minDist = dist;
                    idx = i;
                }
            }
        }
        printf("%d -> ", requests[idx]);
        totalHeadMovement += abs(requests[idx] - head);
        head = requests[idx];
        completed[idx] = 1;
        completedCount++;
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
    SSTF(requests, n, head);
    return 0;
}
