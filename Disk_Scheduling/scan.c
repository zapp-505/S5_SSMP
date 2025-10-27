#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SCAN(int requests[], int n, int head, int diskSize, int direction)
{
    sort(requests, n);

    int totalHeadMovement = 0;
    printf("\nSeek Sequence (SCAN): ");

    // finding the index of the request with current heads value
    int idx = 0;
    while (idx < n && requests[idx] < head)
        idx++;

    if (direction == 1)
    {
        // scans till rightmost req
        for (int i = idx; i < n; i++)
        {
            printf("%d -> ", requests[i]);
            totalHeadMovement += abs(requests[i] - head);
            head = requests[i];
        }

        // scans to end
        printf("%d -> ", diskSize - 1);
        totalHeadMovement += abs((diskSize - 1) - head);
        head = diskSize - 1;

        // back from end to initial-1 and to leftmost req
        for (int i = idx - 1; i >= 0; i--)
        {
            printf("%d -> ", requests[i]);
            totalHeadMovement += abs(requests[i] - head);
            head = requests[i];
        }
    }
    else
    {
        for (int i = idx - 1; i >= 0; i--)
        {
            printf("%d -> ", requests[i]);
            totalHeadMovement += abs(requests[i] - head);
            head = requests[i];
        }
        printf("0 -> ");
        totalHeadMovement += head;
        head = 0;

        for (int i = idx; i < n; i++)
        {
            printf("%d -> ", requests[i]);
            totalHeadMovement += abs(requests[i] - head);
            head = requests[i];
        }
    }

    printf("END\n");
    printf("Total Head Movement = %d\n", totalHeadMovement);
}

int main()
{
    int n, head, diskSize, direction;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // as we reach an end of the disk always
    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    SCAN(requests, n, head, diskSize, direction);
    return 0;
}
