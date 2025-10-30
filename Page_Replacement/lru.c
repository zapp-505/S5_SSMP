#include<stdio.h>

int limit, refString[100], frames, count, flag, frmArr[10], pageFault;

void read(){
    printf("Enter the total number of elements : ");
    scanf("%d",&limit);
    printf("Enter the elements : ");
    for(int i = 0; i < limit; i++){
        scanf("%d",&refString[i]);
    }
    printf("Enter the frames : ");
    scanf("%d",&frames);
}

void reset(){
    count = 0;
    pageFault = 0;
    for(int i = 0; i < frames; i++){
        frmArr[i] = -1;
    }
}

void lru(){
    reset();
    int lru[frames];
    //lru[i] = -1 means that frame i hasn’t been used yet.
    for(int i = 0; i < frames; i++){
        lru[i] = -1;
    }
    for(int i = 0; i < limit; i++){
        flag = 0;
        for(int j = 0; j < frames; j++){
            if(frmArr[j] == refString[i]){
                flag = 1;
                lru[j] = i;//updates the last used time of the frame
                break;
            }
        }
        if(flag == 0){
            int min = 0;
            //min becomes index of lru frame
            for(int j = 1; j < frames; j++){
                if(lru[j] < lru[min]){
                    min = j;
                }
            }
            frmArr[min] = refString[i];
            lru[min] = i;//as the frame is updated it becomes lru
            pageFault++;
        }
        printf("%d ->  ", refString[i]);
        for (int k = 0; k < frames; k++) {
            if(frmArr[k]==-1)
            {
                printf("-  ");
            }
            else{
            printf("%d  ", frmArr[k]);
            }
        }
        printf("\n");
    }
    printf("Page Faults = %d\n",pageFault);
}

void main(){
    read();
    lru();
}