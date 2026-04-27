#include <stdio.h>

#define MAX 10

typedef struct {
    int id, execution, period, remaining;
} Task;

Task tasks[MAX];
int n;

void rate_monotonic(int time_limit) {
    for (int i = 0; i < n; i++)
        tasks[i].remaining = 0;

    for (int t = 0; t < time_limit; t++) {


        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0)
                tasks[i].remaining = tasks[i].execution;
        }

        int min_period = 9999, selected = -1;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", t, tasks[selected].id);
            tasks[selected].remaining--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    int time_limit;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Execution time of Task %d: ", i + 1);
        scanf("%d", &tasks[i].execution);
        printf("Period of Task %d: ", i + 1);
        scanf("%d", &tasks[i].period);
    }

    printf("Enter simulation time: ");
    scanf("%d", &time_limit);

    rate_monotonic(time_limit);

    return 0;
}
