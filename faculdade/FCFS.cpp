#include <stdio.h>

// Definir funções para calcular o tempo de espera, tempo de retorno e média do tempo de espera/retorno

void waiting_time(int processos[][2], int n, int wt[]) {
    int tempo_servico[n];
    tempo_servico[0] = 0;
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        tempo_servico[i] = tempo_servico[i-1] + processos[i-1][1];
        wt[i] = tempo_servico[i] - processos[i][0];
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

void turn_around_time(int processos[][2], int n, int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = processos[i][1] + wt[i];
    }
}

float average_wt(int processos[][2], int n) {
    int wt[n];
    waiting_time(processos, n, wt);
    int total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
    }
    return (float)total_wt / n;
}

float average_tat(int processos[][2], int n) {
    int wt[n], tat[n];
    waiting_time(processos, n, wt);
    turn_around_time(processos, n, tat, wt);
    int total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_tat += tat[i];
    }
    return (float)total_tat / n;
}

int main() {
    // Ler os dados dos processos
    int n;
    printf("Quantidade de Processos: ");
    scanf("%d", &n);
    int processos[n][2];
    for (int i = 0; i < n; i++) {
        printf("Arrival Time do Processo %d: ", i+1);
        scanf("%d", &processos[i][0]);
        printf("Burst Time do Processo %d: ", i+1);
        scanf("%d", &processos[i][1]);
    }

    // Calcular o tempo de espera, tempo de retorno e média do tempo de espera/retorno
    int wt[n], tat[n];
    waiting_time(processos, n, wt);
    turn_around_time(processos, n, tat, wt);
    float avg_wt = average_wt(processos, n);
    float avg_tat = average_tat(processos, n);

    // Imprimir a tabela com os resultados
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, processos[i][1], processos[i][0], wt[i], tat[i], tat[i] + processos[i][0]);
    }
    printf("Average Waiting Time: %f\n", avg_wt);
    printf("Average Turn-Around Time: %f\n", avg_tat);

    return 0;
}