#include "include/integral_concorrente.h"

#define DIVISOES_NO_INTERVALO 128

//argumentos passados à função chamada por pthread_create
typedef struct {
    double(*func)(double);
    double inicio;
    double erro;
} argumento_t;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int indice_intervalo = 0;
static double tamanho_intervalo;

//funcao chamada por pthread_create
static void* thread_func(void* arg) {
    argumento_t argumento = *(argumento_t*)arg;
    double soma = 0;    //soma das integrais calculadas pela thread

    Pthread_mutex_lock(&mutex);
    while(indice_intervalo < DIVISOES_NO_INTERVALO) {
        double a = argumento.inicio + tamanho_intervalo * indice_intervalo; //inicio do intervalo
        double b = a + tamanho_intervalo;   //fim do intervalo
        indice_intervalo++;
        Pthread_mutex_unlock(&mutex);
        soma += integral_sequencial(argumento.func, a, b, argumento.erro);
        Pthread_mutex_lock(&mutex);
    }
    Pthread_mutex_unlock(&mutex);

    double* resultado = (double*)Malloc(sizeof(double));
    *resultado = soma;
    
    pthread_exit(resultado);
}


/*
Calcula a integral de 'func' no intervalo [a,b].

args:
    func: função que será integrada.
    a: primeiro valor do intervalo sobre o qual será calculada a integral
    b: segundo valor do intervalo sobre o qual será calculada a integral
    erro: erro absoluto admitido no valor numérico da integral
    n_threads: número de threads que devem ser utilizadas
retorno:
    valor da integral calculado numericamente
*/
double integral_concorrente( double(*func)(double), double a, double b, double erro, int n_threads ) {

    pthread_t* threads = (pthread_t*)Malloc(sizeof(pthread_t) * n_threads);
    argumento_t argumento = {func, a, erro};

    indice_intervalo = 0;
    tamanho_intervalo = (b - a) / DIVISOES_NO_INTERVALO;
    
    //cria threads
    for(int i = 0; i < n_threads; i++) {
        Pthread_create(threads + i, NULL, thread_func, &argumento);
    }

    double soma = 0;

    //recolhe threads
    for(int i = 0; i < n_threads; i++) {

        double* resultado;
        Pthread_join(threads[i], (void**)&resultado);
        soma += *resultado;
        free(resultado);
    }
    free(threads);
    return soma;
}