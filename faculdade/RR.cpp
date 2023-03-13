#include <stdio.h>
#include <stdbool.h>

void round_robin(int processos[][3], int quantum, int qnt_processos, int bt_restante[], int wt[]) {
int tempo = 0;
int overhead = 1;

while (true) {
    bool finalizados = true;
    for (int i = 0; i < qnt_processos; i++) {
        tempo += overhead;

        if (bt_restante[i] > 0) {
            finalizados = false;

            if (bt_restante[i] > quantum) {
                tempo += quantum;
                bt_restante[i] -= quantum;
            } else {
                tempo += bt_restante[i];
                wt[i] = tempo - processos[i][2];
                bt_restante[i] = 0;
            }
        }
    }
    if (finalizados == true) {
        break;
    }
}
}

void turn_around_time(int processos[][3], int wt[], int qnt_processos, int tat[]) {
for (int i = 0; i < qnt_processos; i++) {
tat[i] = processos[i][2] + wt[i];
}
}

float average_tat(int tat[], int qnt_processos) {
float sum = 0;
for (int i = 0; i < qnt_processos; i++) {
sum += tat[i];
}
return (sum / qnt_processos);
}

float average_wt(int wt[], int qnt_processos) {
float sum = 0;
for (int i = 0; i < qnt_processos; i++) {
sum += wt[i];
}
return (sum / qnt_processos);
}

int main() {
int qnt_processos, quantum;

printf("Algoritmo Round Robin\n");
printf("Quantidade de processos: ");
scanf("%d", &qnt_processos);

int processos[qnt_processos][3];
int bt_restante[qnt_processos];
int wt[qnt_processos];
int tat[qnt_processos];

for (int i = 0; i < qnt_processos; i++) {
    printf("Arrival Time do processo %d: ", i + 1);
    scanf("%d", &processos[i][1]);

    printf("Burst Time do processo %d: ", i + 1);
    scanf("%d", &processos[i][2]);

    bt_restante[i] = processos[i][2];
}

printf("Informe o Quantum: ");
scanf("%d", &quantum);

round_robin(processos, quantum, qnt_processos, bt_restante, wt);
turn_around_time(processos, wt, qnt_processos, tat);
float avg_tat = average_tat(tat, qnt_processos);
float avg_wt = average_wt(wt, qnt_processos);

printf("| Process |\t| Burst Time |\t\t| Arrival Time |\t| Waiting Time |\t| Turn-Around Time |\t\n\n");
for (int i = 0; i < qnt_processos; i++) {
    printf("| %i \t| \t%d \t| \t%d \t| \t%d \t| \t%d \t| \n", processos[i][0], processos[i][2], processos[i][1], wt[i], tat[i]);
}

printf("Average Waiting Time: %f\n", avg_wt);
printf("Average Turn-Around Time: %f\n", avg_tat);
}