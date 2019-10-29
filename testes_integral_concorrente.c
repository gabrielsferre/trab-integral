//#include "include/integral_concorrente.h" está dando erro de compilação
#include <pthread.h>
#include <stdio.h>
#include "include/timer.h"
#include "include/funcoes.h"

/*
Testes de corretude e tempo de execução para o cálculo concorrente
de integrais.
*/

#define N_THREADS 4

extern double integral_concorrente( double(*func)(double), double a, double b, double erro, int n_threads );

double my_abs(double n) {
    return n < 0 ? -n : n;
}

void teste(double(*func)(double), double a, double b, double resultado_esperado, double erro, const char nome_teste[]) {
    double tempo_0;
    double tempo;

    GET_TIME(tempo_0);
    double resultado = integral_concorrente(func, a, b, erro, N_THREADS);
    GET_TIME(tempo);

    tempo = tempo - tempo_0;

    erro = my_abs(erro);
    if( my_abs(resultado - resultado_esperado) > erro ) {
        printf("Erro no teste \"%.64s\"\n", nome_teste);
        printf("Resultado esperado: %.10f\n", resultado_esperado);
        printf("Resultado obtido: %.10f\n\n", resultado);
    }
    else {
        printf("Passou no teste \"%.64s\"\n", nome_teste);
    }
    printf("Intervalo: [%.6f, %.6f]\n", a, b);
    printf("Erro: %.10f\n", erro);
    printf("Numero de threads: %d\n", N_THREADS);
    printf("Tempo: %.10f\n\n", tempo);
}

int main() {
    teste(cos, 0, PI/2, 1, 1e-6, "cosseno");
    teste(exp, 1, 0, 1 - E_NUM, 1e-5, "exponencial");
    teste(func_a, 2, 7, 27.5, 1e-5, "função a");
    teste(func_b, -1, 1, PI/2, 1e-5, "função b");
    teste(func_c, -20, 100, 336002, 1, "função c");
    teste(func_d, -8, -0.55, 0.546625, 1e-6, "função d");
    teste(func_e, -8, -0.55, -0.46402, 1e-5, "função e");
    teste(func_f, -10, 20, 200.245, 1e-3, "função f");
    teste(func_g, -2, 1, 0.562653, 1e-6, "função g");
}