#include <stdio.h>

void waiting_time(int n, int processos[][3], int wt[]) {
    int tempo_servico[n];
    tempo_servico[0] = 0;
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        tempo_servico[i] = tempo_servico[i-1] + processos[i-1][2];
        wt[i] = tempo_servico[i] - processos[i][1];
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

void turn_around_time(int n, int processos[][3], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = processos[i][2] + wt[i];
    }
}

float average_tat(int n, int processos[][3]) {
    int tat[n], sum = 0;
    float avg;
    int wt[n];
    waiting_time(n, processos, wt);
    turn_around_time(n, processos, tat, wt);
    for (int i = 0; i < n; i++) {
        sum += tat[i];
    }
    avg = (float) sum / n;
    return avg;
}

float average_wt(int n, int processos[][3]) {
    int wt[n], sum = 0;
    float avg;
    waiting_time(n, processos, wt);
    for (int i = 0; i < n; i++) {
        sum += wt[i];
    }
    avg = (float) sum / n;
    return avg;
}

void SJF(int n, int processos[][3]) {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (processos[j][2] > processos[j+1][2]) {
                for (int k = 0; k < 3; k++) {
                    temp = processos[j][k];
                    processos[j][k] = processos[j+1][k];
                    processos[j+1][k] = temp;
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Quantidade de processos: ");
    scanf("%d", &n);
    int processos[n][3];
    char pid[3];
    for (int i = 0; i < n; i++) {
        sprintf(pid, "P%d", i);
        printf("Arrival Time do %s: ", pid);
        scanf("%d", &processos[i][1]);
        printf("Burst Time do %s: ", pid);
        scanf("%d", &processos[i][2]);
        processos[i][0] = i;
    }
    SJF(n, processos);
    int wt[n], tat[n];
    waiting_time(n, processos, wt);
    turn_around_time(n, processos, tat, wt);
    printf("\n| Process |\t| Burst Time |\t\t| Arrival Time |\t| Waiting Time |\t| Turn-Around Time |\t| Completion Time |\n\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", pid, processos[i][2], processos[i][1],wt[i], tat[i], tat[i] + processos[i][1]);
}
float avgwt = average_wt(n, processos);
float avgtat = average_tat(n, processos);
printf("\nAverage Waiting Time: %f", avgwt);
printf("\nAverage Turn-Around Time: %f\n", avgtat);
return 0;
}
