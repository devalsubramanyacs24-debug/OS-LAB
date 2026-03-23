#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to calculate waiting and turnaround times using FCFS
void fcfs(struct Process p[], int n) {
    int i;

    // First process has 0 waiting time
    p[0].waiting_time = 0;

    // Calculate waiting time
    for (i = 1; i < n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

// Function to display results
void display(struct Process p[], int n, char queue_name[]) {
    int i;
    float total_wt = 0, total_tat = 0;

    printf("\n--- %s Queue ---\n", queue_name);
    printf("PID\tBT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n_sys, n_user, i;

    printf("Enter number of system processes: ");
    scanf("%d", &n_sys);

    struct Process sys[n_sys];

    printf("\nEnter burst time for system processes:\n");
    for (i = 0; i < n_sys; i++) {
        sys[i].pid = i + 1;
        printf("P%d: ", sys[i].pid);
        scanf("%d", &sys[i].burst_time);
    }

    printf("\nEnter number of user processes: ");
    scanf("%d", &n_user);

    struct Process user[n_user];

    printf("\nEnter burst time for user processes:\n");
    for (i = 0; i < n_user; i++) {
        user[i].pid = i + 1;
        printf("P%d: ", user[i].pid);
        scanf("%d", &user[i].burst_time);
    }

    // Apply FCFS on system queue first
    fcfs(sys, n_sys);

    // Apply FCFS on user queue
    fcfs(user, n_user);

    // Display results
    display(sys, n_sys, "System (High Priority)");
    display(user, n_user, "User (Low Priority)");

    return 0;
}
