#include <stdio.h>

int main()
{
    int i, n, time = 0, remain, tq;
    int bt[20], rt[20], wt[20], tat[20];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter Burst Time for Process P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // Remaining time = Burst time initially
    }

    remain = n;

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    while(remain != 0)
    {
        for(i = 0; i < n; i++)
        {
            if(rt[i] > 0)
            {
                if(rt[i] <= tq)
                {
                    time += rt[i];
                    rt[i] = 0;

                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];

                    total_wt += wt[i];
                    total_tat += tat[i];

                    remain--;
                }
                else
                {
                    time += tq;
                    rt[i] -= tq;
                }
            }
        }
    }

    printf("\nProcess\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", i+1, bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}
