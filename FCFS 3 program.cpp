#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

void fcfs(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0, current_time = 0;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int waiting_time = current_time - processes[i].arrival_time;
        int turnaround_time = waiting_time + processes[i].burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, waiting_time, turnaround_time);

        current_time += processes[i].burst_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    struct Process processes[] = {
        {1, 0, 5},
        {2, 0, 3},
        {3, 0, 8}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    fcfs(processes, n);

    return 0;
}

