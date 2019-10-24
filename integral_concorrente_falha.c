#include "include/integral_concorrente.h"

#define RECURSAO_MAX 20

typedef double my_float;

typedef struct {
    my_float a;
    my_float b;
} intervalo_t;

typedef intervalo_t tipo_fila; 

#include "include/fila.h"

//argumentos passados à função chamada por pthread_create
typedef struct {
    my_float(*func)(my_float);
    my_float erro;
} argumento_t;

static my_float soma_integral = 0;
static int nos_recursao_abertos = 0;
static int nos_recursao_fechados = 0;
static Fila intervalos_fila;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int n_threads = 3;

static void reseta_variaveis_globais() {
    soma_integral = 0;
    nos_recursao_abertos = 0;
    nos_recursao_fechados = 0;
    fila_delete(&intervalos_fila);
}

static my_float my_abs(my_float n) {
    return n < 0 ? -n : n;
}

static int pow_2(int n) {
    int r = 1;
    while(n > 0) {
        r *= 2;
        n--;
    }
    return r;
}

static void integral_recursiva( my_float(*func)(my_float), my_float a, my_float b, my_float erro, int nivel_recursao) {
    if(nivel_recursao >= RECURSAO_MAX) {
        intervalo_t intervalo = {a,b};
        Pthread_mutex_lock(&mutex);
        fila_insere(&intervalos_fila, intervalo);
        nos_recursao_abertos += pow_2(RECURSAO_MAX - 1) - 1;


        // printf("abertos: %d\n", nos_recursao_abertos);
        // printf("fechados: %d\n", nos_recursao_fechados);



        Pthread_cond_signal(&cond);
        Pthread_mutex_unlock(&mutex);
        return;
    }

    my_float c = (a+b)/2;    //ponto medio entre a e b
    my_float a_c = (a+c)/2;  //ponto medio entre a e c
    my_float c_b = (c+b)/2;  //ponto medio entre c e b
    my_float f_c = func(c);  //altura do retangulo com base ab 
    my_float f_a_c = func(a_c);  //altura do retangulo com base ac
    my_float f_c_b = func(c_b);  //altura do retangulo com base 
    my_float integral_c = f_c * (b - a);
    my_float integral_a_c = f_a_c * (a_c - a);
    my_float integral_c_b = f_c_b * (b - c_b);

    erro = my_abs(erro);
    if( my_abs( integral_c - (integral_a_c + integral_c_b) ) <= erro/10 ) {
        Pthread_mutex_lock(&mutex);
        soma_integral += integral_c;
        nos_recursao_fechados++;
        nos_recursao_abertos -= pow_2(RECURSAO_MAX - nivel_recursao);
        nos_recursao_abertos++;
        Pthread_mutex_unlock(&mutex);
        return;
    }
    integral_recursiva(func, a, c, erro, nivel_recursao + 1);
    integral_recursiva(func, c, b, erro, nivel_recursao + 1);
}

static void* thread_func(void* arg) {
    argumento_t argumento = *(argumento_t*)arg;
    while(1) {
        Pthread_mutex_lock(&mutex);
        while(intervalos_fila.n_elementos == 0 && nos_recursao_abertos > nos_recursao_fechados) {
            // printf("esperando\n");
            Pthread_cond_wait(&cond, &mutex);
        }




        // printf("elementos na fila: %d\n",intervalos_fila.n_elementos);
        // printf("abertos: %d\n", nos_recursao_abertos);
        // printf("fechados: %d\n", nos_recursao_fechados);







        if( nos_recursao_abertos <= nos_recursao_fechados ) {
            Pthread_cond_broadcast(&cond);
            Pthread_mutex_unlock(&mutex);   
            break;
        }
        intervalo_t intervalo = fila_remove(&intervalos_fila);


        // printf("removendo elemento da fila\n");


        Pthread_mutex_unlock(&mutex);
        integral_recursiva(argumento.func, intervalo.a, intervalo.b, argumento.erro, 1);
    }
    pthread_exit(NULL);
}

my_float integral_concorrente( my_float(*func)(my_float), my_float a, my_float b, my_float erro ) {

    fila_init(&intervalos_fila);
    pthread_t* threads = (pthread_t*)Malloc(sizeof(pthread_t) * n_threads);
    argumento_t argumento = {func, erro};

    nos_recursao_abertos += pow_2(RECURSAO_MAX - 1) - 1;
    integral_recursiva(func, a, b, erro, 1);
    
    for(int i = 0; i < n_threads; i++) {
        Pthread_create(threads + i, NULL, thread_func, &argumento);
    }
    for(int i = 0; i < n_threads; i++) {
        Pthread_join(threads[i], NULL);
    }
    my_float resultado = soma_integral;
    reseta_variaveis_globais();
    return resultado;
}




#include "include/timer.h"
#include "include/funcoes.h"
void teste(my_float(*func)(my_float), my_float a, my_float b, my_float resultado_esperado, my_float erro, const char nome_teste[]) {
    double tempo_0;
    double tempo;

    GET_TIME(tempo_0);
    my_float resultado = integral_concorrente(func, a, b, erro);
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
    // teste(exp, 1, 0, 1 - E_NUM, 1e-5, "exponencial");
    // teste(func_a, 2, 7, 27.5, 1e-5, "função a");
    // teste(func_b, -1, 1, PI/2, 1e-5, "função b");
    // teste(func_c, -20, 100, 336002, 1, "função c");
    // teste(func_d, -8, -0.55, 0.546625, 1e-6, "função d");
    // teste(func_e, -8, -0.55, -0.46402, 1e-5, "função e");
    // teste(func_f, -10, 20, 200.245, 1e-3, "função f");
    // teste(func_g, -2, 1, 0.562653, 1e-6, "função g");
}