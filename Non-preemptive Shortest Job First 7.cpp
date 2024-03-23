#include <stdio.h>
#include <limits.h>

struct Process {
    int burst_time;
    int completed;
};

int main() {
    struct Process processes[] = {{6, 0}, {2, 0}, {8, 0}}; // Burst time of processes
    int n = sizeof(processes) / sizeof(processes[0]);
    int total_waiting_time = 0, total_turnaround_time = 0, current_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    while (1) {
        int shortest_job_index = -1, shortest_job_duration = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].burst_time < shortest_job_duration) {
                shortest_job_index = i;
                shortest_job_duration = processes[i].burst_time;
            }
        }

        if (shortest_job_index == -1) {
            break;
        }

        struct Process *current_process = &processes[shortest_job_index];
        current_time += current_process->burst_time;
        current_process->completed = 1;

        int waiting_time = current_time - current_process->burst_time;
        int turnaround_time = waiting_time + current_process->burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\n", shortest_job_index + 1, current_process->burst_time,
               waiting_time, turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}

