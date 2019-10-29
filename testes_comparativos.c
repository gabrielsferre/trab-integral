#include <pthread.h>
#include <stdio.h>
#include "include/timer.h"
#include "include/funcoes.h"
#include "include/integral_sequencial.h"

/*
Testes que comparam o tempo entre o cálculo sequencial e o concorrente 
*/

#define N_THREADS 4

extern double integral_concorrente( double(*func)(double), double a, double b, double erro, int n_threads );

void teste(double(*func)(double), double a, double b, double erro, const char nome_teste[]) {
    double tempo_0;
    double tempo_seq;
    double tempo_conc;

    GET_TIME(tempo_0);
    double resultado_seq = integral_sequencial(func, a, b, erro);
    GET_TIME(tempo_seq);
    tempo_seq = tempo_seq - tempo_0;

    GET_TIME(tempo_0);
    double resultado_conc = integral_concorrente(func, a, b, erro, N_THREADS);
    GET_TIME(tempo_conc);
    tempo_conc = tempo_conc - tempo_0;

    printf("Teste \"%.60s\"\n", nome_teste);
    printf("Resultado sequencial: %.10f\n", resultado_seq);
    printf("Resultado concorrente: %.10f\n", resultado_conc);
    printf("Tempo sequencial: %.10f\n", tempo_seq);
    printf("Tempo concorrente: %.10f\n", tempo_conc);
    printf("Ganho concorrente: %.2f\n\n", tempo_seq / tempo_conc);
}

int main() {
    teste(cos, 0, PI/2, 1e-6, "cosseno");
    teste(exp, 1, 0, 1e-5, "exponencial");
    teste(func_a, 2, 7, 1e-5, "função a");
    teste(func_b, -1, 1, 1e-5, "função b");
    teste(func_c, -20, 100, 1, "função c");
    teste(func_d, -8, -0.55, 1e-6, "função d");
    teste(func_e, -8, -0.55, 1e-5, "função e");
    teste(func_f, -10, 20, 1e-3, "função f");
    teste(func_g, -2, 1, 1e-6, "função g");
}