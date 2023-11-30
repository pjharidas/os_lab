#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

// Function prototypes
void getProcessInfo(int selected_algorithm);
void calculateFCFS();
void calculateSJF();
void calculatePriority();
void calculateRoundRobin(int time_quantum);
void calculateAverageTimes(float *avg_waiting_time, float *avg_turnaround_time);
void displayResults(float avg_waiting_time, float avg_turnaround_time);

int num_of_process;
int arrival_time[MAX_PROCESS];
int burst_time[MAX_PROCESS];
int completion_time[MAX_PROCESS];
int waiting_time[MAX_PROCESS];
int turnaround_time[MAX_PROCESS];
int response_time[MAX_PROCESS];
int priority[MAX_PROCESS];

int main() {
    int selected_algorithm;
    int time_quantum;

    printf("Select a scheduling algorithm:\n");
    printf("1. FCFS (First-Come-First-Served)\n");
    printf("2. SJF (Shortest Job First)\n");
    printf("3. Priority Scheduling\n");
    printf("4. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &selected_algorithm);

    getProcessInfo(selected_algorithm);

    switch (selected_algorithm) {
        case 1:
            calculateFCFS();
            break;
        case 2:
            calculateSJF();
            break;
        case 3:
            calculatePriority();
            break;
        case 4:
            printf("Enter Time Quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            calculateRoundRobin(time_quantum);
            break;
        default:
            printf("Invalid choice. Please select a valid scheduling algorithm.\n");
            return 1;
    }

    float avg_waiting_time, avg_turnaround_time;
    calculateAverageTimes(&avg_waiting_time, &avg_turnaround_time);

    displayResults(avg_waiting_time, avg_turnaround_time);

    return 0;
}

void getProcessInfo(int selected_algorithm) {
    printf("Enter total number of processes (maximum %d): ", MAX_PROCESS);
    scanf("%d", &num_of_process);

    if (num_of_process < 1 || num_of_process > MAX_PROCESS) {
        printf("Invalid number of processes. Please enter a number between 1 and %d.\n", MAX_PROCESS);
        exit(1);
    }

    for (int i = 0; i < num_of_process; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);

        if (selected_algorithm == 3) {
            printf("Priority: ");
            scanf("%d", &priority[i]);
        }
    }
}

void calculateFCFS() {
    int current_time = 0;

    for (int i = 0; i < num_of_process; i++) {

        response_time[i] = current_time - arrival_time[i];

        completion_time[i] = 
        (current_time < arrival_time[i]) 
        ? arrival_time[i] + burst_time[i]
        : current_time + burst_time[i];

        current_time = completion_time[i];

        waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];

        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculateSJF(int selected_algorithm) {
    // These loops are responsible for arrenging the processes burst and arrival times in ascending order
        
    for (int i = 0; i < num_of_process - 1; i++) {
        for (int j = 0; j < num_of_process - i - 1; j++) {
            if (burst_time[j] > burst_time[j + 1]) {
                // if burst time[j] > it's next one:
                //      swap it with the next
                int temp_burst = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp_burst;

                // also need to swap the corresponding arrival times
                int temp_arrival = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp_arrival;

                // also need to swap the corresponding Priorities if it's a priority scheduling 
                if (selected_algorithm == 3) {
                    int temp_priority = priority[j];
                    priority[j] = priority[j + 1];
                    priority[j + 1] = temp_priority;
                }
            }
        }
    }


// After the processess are sorted then it's just FCFS EZPZ
    int current_time = 0;

    for (int i = 0; i < num_of_process; i++) {

        response_time[i] = current_time - arrival_time[i];

        completion_time[i] = 
        (current_time < arrival_time[i]) 
        ? arrival_time[i] + burst_time[i] 
        : current_time + burst_time[i];

        current_time = completion_time[i];

        waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];

        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculatePriority() {
    for (int i = 0; i < num_of_process - 1; i++) {
        for (int j = 0; j < num_of_process - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                // Ascending order of priority
                int temp_priority = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp_priority;

                int temp_arrival = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp_arrival;

                int temp_burst = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp_burst;
            }
        }
    }

// Then it's just FCFS
    int current_time = 0;

    for (int i = 0; i < num_of_process; i++) {
        response_time[i] = current_time - arrival_time[i];
        completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
        current_time = completion_time[i];
        waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculateRoundRobin(int time_quantum) {
    int remaining_time[MAX_PROCESS];
    for (int i = 0; i < num_of_process; i++) {
        remaining_time[i] = burst_time[i];
    }

    int current_time = 0;

    while (1) {
        int done = 1;

        for (int i = 0; i < num_of_process; i++) {
            if (remaining_time[i] > 0) {
                done = 0;

                if (remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    current_time += remaining_time[i];
                    completion_time[i] = current_time;
                    waiting_time[i] = current_time - burst_time[i] - arrival_time[i];
                    turnaround_time[i] = completion_time[i] - arrival_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if (done == 1) {
            break;
        }
    }
}

void calculateAverageTimes(float *avg_waiting_time, float *avg_turnaround_time) {
    *avg_waiting_time = 0.0;
    *avg_turnaround_time = 0.0;

    for (int i = 0; i < num_of_process; i++) {
        *avg_waiting_time += waiting_time[i];
        *avg_turnaround_time += turnaround_time[i];
    }

    *avg_waiting_time /= num_of_process;
    *avg_turnaround_time /= num_of_process;
}

void displayResults(float avg_waiting_time, float avg_turnaround_time) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < num_of_process; i++) {
        printf("%d\t%d\t\t\t%d\t\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i], response_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}
