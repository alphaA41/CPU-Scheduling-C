#include<stdio.h>

#define MAX 9999

typedef struct {
    int no, at, bt, wt, tat, ct, temp;
} process;

void readProcess(process *p, int i) {
    printf("\nProcess No: %d\n", i);
    p->no = i;
    printf("Enter Arrival Time: ");
    scanf("%d", &p->at);
    printf("Enter Burst Time: ");
    scanf("%d", &p->bt);
    p->temp = p->bt;
}

void main() {
    int n, remaining, min_val, min_index;
    float avgtat = 0, avgwt = 0;
    printf("Shortest Job First Scheduling (Preemptive)______\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    process p[n], temp;
    remaining = n;
    //reading values of processes
    for (int i = 0; i < n; i++) {
        readProcess(&p[i], i + 1);
    }

    //bubble sort based on at
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    //implementation (heart of program)
    for (int c = p[0].at; remaining > 0; c++) {
        min_val = MAX, min_index = -1;
        for (int i=0; i<n; i++) {
            if (p[i].at <= c && p[i].temp < min_val) {
                min_val = p[i].temp;
                min_index = i;
            }
        }    
        if (min_index == -1) {
            continue;
        }
        p[min_index].temp--;
        if (p[min_index].temp == 0) {
            p[min_index].temp = MAX;
            p[min_index].ct = c + 1;
            p[min_index].tat = p[min_index].ct - p[min_index].at;
            p[min_index].wt = p[min_index].tat - p[min_index].bt;
            avgtat += p[min_index].tat;
            avgwt += p[min_index].wt;
            remaining--;
        }    
    }
    //////////////////////////////////////
    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    avgtat /= n;
    avgwt /= n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat, avgwt);
}
