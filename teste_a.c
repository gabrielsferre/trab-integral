#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/timer.h"
#include "include/funcoes.h"
#include "include/integral_sequencial.h"

extern double integral_concorrente( double(*func)(double), double a, double b, double erro, int n_threads );

void teste(double(*func)(double), double a, double b, double erro, int n_threads) {
    double tempo_0;
    double tempo_seq;
    double tempo_conc;

    GET_TIME(tempo_0);
    double resultado_seq = integral_sequencial(func, a, b, erro);
    GET_TIME(tempo_seq);
    tempo_seq = tempo_seq - tempo_0;

    GET_TIME(tempo_0);
    double resultado_conc = integral_concorrente(func, a, b, erro, n_threads);
    GET_TIME(tempo_conc);
    tempo_conc = tempo_conc - tempo_0;

    printf("Resultado sequencial: %.10f\n", resultado_seq);
    printf("Resultado concorrente: %.10f\n", resultado_conc);
    printf("Tempo sequencial: %.10f\n", tempo_seq);
    printf("Tempo concorrente: %.10f\n", tempo_conc);
    printf("Ganho concorrente: %.2f\n\n", tempo_seq / tempo_conc);
}

int main(int argc, char* argv[]) {
    if(argc != 5) {
        printf("Número errado de argumentos!\n");
        printf("Argumentos: os dois limites de integração, erro máximo e número de threads\n");
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double erro = atof(argv[3]);
    int n_threads = atoi(argv[4]);

    teste(func_a, a, b, erro, n_threads);
}