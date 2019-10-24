#include "include/integral_concorrente.h"
#include "include/integral_sequencial.h"

#include "include/timer.h"
#include "include/funcoes.h"

#define DIVISOES_NO_INTERVALO 10

typedef double my_float;

//argumentos passados à função chamada por pthread_create
typedef struct {
    my_float(*func)(my_float);
    my_float inicio;
    my_float erro;
} argumento_t;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int indice_intervalo = 0;
static my_float tamanho_intervalo;

static my_float my_abs(my_float n) {
    return n < 0 ? -n : n;
}


static void* thread_func(void* arg) {
    argumento_t argumento = *(argumento_t*)arg;
    my_float soma = 0;

    Pthread_mutex_lock(&mutex);
    while(indice_intervalo < DIVISOES_NO_INTERVALO) {
        my_float a = argumento.inicio + tamanho_intervalo * indice_intervalo;
        my_float b = a + tamanho_intervalo;
        indice_intervalo++;

        Pthread_mutex_unlock(&mutex);
        soma += integral_sequencial(argumento.func, a, b, argumento.erro);
        Pthread_mutex_lock(&mutex);
    }
    Pthread_mutex_unlock(&mutex);

    my_float* resultado = (my_float*)Malloc(sizeof(my_float));
    *resultado = soma;
    
    pthread_exit(resultado);
}

my_float integral_concorrente( my_float(*func)(my_float), my_float a, my_float b, my_float erro, int n_threads ) {

    pthread_t* threads = (pthread_t*)Malloc(sizeof(pthread_t) * n_threads);
    argumento_t argumento = {func, a, erro};

    indice_intervalo = 0;
    tamanho_intervalo = (b - a) / DIVISOES_NO_INTERVALO;
    
    for(int i = 0; i < n_threads; i++) {
        Pthread_create(threads + i, NULL, thread_func, &argumento);
    }

    my_float soma = 0;
    for(int i = 0; i < n_threads; i++) {

        my_float* resultado;
        Pthread_join(threads[i], (void**)&resultado);
        soma += *resultado;
        free(resultado);
    }
    free(threads);
    return soma;
}


void teste(my_float(*func)(my_float), my_float a, my_float b, my_float resultado_esperado, my_float erro, const char nome_teste[]) {
    double tempo_0;
    double tempo;

    GET_TIME(tempo_0);
    my_float resultado = integral_concorrente(func, a, b, erro, 3);
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