#include <stdio.h>
#include <limits.h>

struct Process {
    int burst_time;
    int completed;
};

int main() {
    struct Process processes[] = {{6, 0}, {2, 0}, {8, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);
    int total_waiting_time = 0, total_turnaround_time = 0, current_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int shortest_job_index = -1, shortest_job_duration = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!processes[j].completed && processes[j].burst_time < shortest_job_duration) {
                shortest_job_index = j;
                shortest_job_duration = processes[j].burst_time;
            }
        }

        struct Process *current_process = &processes[shortest_job_index];
        current_time += current_process->burst_time;
        current_process->completed = 1;

        int waiting_time = current_time - current_process->burst_time;
        int turnaround_time = waiting_time + current_process->burst_time;

        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, current_process->burst_time, waiting_time, turnaround_time);
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}

