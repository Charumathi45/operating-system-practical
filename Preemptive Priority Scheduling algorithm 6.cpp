#include <stdio.h>
#include <limits.h>

struct Process {
    int priority;
    int burst_time;
    int remaining_time;
};

int main() {
    struct Process processes[] = {{2, 6, 6}, {1, 2, 2}, {3, 8, 8}}; 
    int n = sizeof(processes) / sizeof(processes[0]);
    int total_waiting_time = 0, total_turnaround_time = 0, current_time = 0;

    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");

    while (1) {
        int highest_priority_index = -1, highest_priority = INT_MIN;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].priority > highest_priority) {
                highest_priority_index = i;
                highest_priority = processes[i].priority;
            }
        }

        if (highest_priority_index == -1) {
            break;
        }

        struct Process *current_process = &processes[highest_priority_index];
        current_process->remaining_time--;

        if (current_process->remaining_time == 0) {
            int waiting_time = current_time - current_process->burst_time;
            int turnaround_time = waiting_time + current_process->burst_time;

            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;

            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", highest_priority_index + 1, current_process->priority,
                   current_process->burst_time, waiting_time, turnaround_time);
        }

        current_time++;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}

