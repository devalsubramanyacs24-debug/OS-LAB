#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id, execution, remaining;
} Task;

Task tasks[MAX];
int tickets[MAX];
int n;

void proportional(int time_limit) {

    // Assign tickets proportional to execution time
    for (int i = 0; i < n; i++) {
        tickets[i] = tasks[i].execution * 10;
        tasks[i].remaining = tasks[i].execution;
    }

    for (int t = 0; t < time_limit; t++) {

        int total = 0;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0)
                total += tickets[i];
        }

        if (total == 0) {
            printf("Time %d: Idle\n", t);
            continue;
        }

        int winner = rand() % total;
        int sum = 0, selected = -1;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                sum += tickets[i];
                if (winner < sum) {
                    selected = i;
                    break;
                }
            }
        }

        printf("Time %d: Task %d\n", t, tasks[selected].id);
        tasks[selected].remaining--;
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
    }

    printf("Enter simulation time: ");
    scanf("%d", &time_limit);

    proportional(time_limit);

    return 0;
}
