#include <stdio.h>
#include <limits.h>

struct Process {
    int priority;
    int burst_time;
};

int main() {
    struct Process processes[] = {{3, 6}, {1, 2}, {2, 8}}; 
    int n = sizeof(processes) / sizeof(processes[0]);
    int total_waiting_time = 0, total_turnaround_time = 0, current_time = 0;

    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int highest_priority_index = -1, highest_priority = INT_MIN;

        for (int j = 0; j < n; j++) {
            if (processes[j].priority > highest_priority) {
                highest_priority_index = j;
                highest_priority = processes[j].priority;
            }
        }

        struct Process *current_process = &processes[highest_priority_index];
        current_time += current_process->burst_time;

        int waiting_time = current_time - current_process->burst_time;
        int turnaround_time = waiting_time + current_process->burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, current_process->priority,
            current_process->burst_time, waiting_time, turnaround_time);

        current_process->priority = INT_MIN; 
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}

