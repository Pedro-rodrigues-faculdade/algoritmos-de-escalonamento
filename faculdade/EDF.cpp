#include <stdio.h>

void print_contador(int contador[], int qnt) {
    for (int i = 0; i < qnt; i++) {
        printf("O Processo P%d Executou %d vezes\n", i, contador[i]);
    }
}

void edf(int processos[][4], int qnt) {
    int relogio = 0;
    int deadlines[qnt];
    int periodos[qnt];
    int contador[qnt];

    for (int i = 0; i < qnt; i++) {
        deadlines[i] = processos[i][2];
        periodos[i] = processos[i][3];
        contador[i] = 0;
    }

    printf("Processos:\n");
    for (int i = 0; i < qnt; i++) {
        printf("[%d, %d, %d, %d]\n", processos[i][0], processos[i][1], processos[i][2], processos[i][3]);
    }
    printf("\n");

    printf("Deadlines:");
    for (int i = 0; i < qnt; i++) {
        printf(" %d", deadlines[i]);
    }
    printf("\n");

    printf("Periodos:");
    for (int i = 0; i < qnt; i++) {
        printf(" %d", periodos[i]);
    }
    printf("\n\n");

    while (1) {
        int escolhido = -1;
        int menor_deadline = 10000;

        for (int i = 0; i < qnt; i++) {
            if (deadlines[i] < menor_deadline) {
                menor_deadline = deadlines[i];
                escolhido = i;
            }
        }

        printf("Processo Escolhido: %d\n", escolhido);

        if (periodos[escolhido] >= relogio) {
            relogio += processos[escolhido][1];
            printf("Processo: P%d executando...\n", escolhido);
            printf("Relogio: %d\n", relogio);
            printf("Burst Time do Processo P%d: %d\n", escolhido, processos[escolhido][1]);

            printf("Deadline ANTERIOR do Processo: %d\n", deadlines[escolhido]);
            deadlines[escolhido] += processos[escolhido][3];
            printf("Deadline do Processo P%d Atualizada: %d\n", escolhido, deadlines[escolhido]);

            printf("Periodo ANTERIOR do Processo: %d\n", periodos[escolhido]);
            periodos[escolhido] += processos[escolhido][3];
            printf("Periodo do Processo P%d Atualizado: %d\n\n", escolhido, periodos[escolhido]);

            contador[escolhido] += 1;
        }

        if (relogio >= 20) {
            break;
        }
    }

    print_contador(contador, qnt);
}

int main() {
    int processos[][4] = {{0, 3, 7, 20},
                           {1, 2, 4, 5},
                           {2, 2, 8, 10}};
    int qnt = sizeof(processos)/sizeof(processos[0]);

    edf(processos, qnt); }
