#include "include/integral_concorrente.h"
#include "math.h"

#define RECURSAO_MAX 10

typedef double my_float;

typedef struct {
    my_float a;
    my_float b;
} intervalo_t;

typedef intervalo_t tipo_fila; 

#include "include/fila.h"

static my_float soma_integral = 0;
static int nos_recursao_abertos = 0;
static int nos_recursao_fechados = 0;
static Fila intervalos_fila;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
    if(nivel_recursao == RECURSAO_MAX) {
        intervalo_t intervalo = {a,b};
        pthread_mutex_lock(&mutex);
        fila_insere(&intervalos_fila, intervalo);
        nos_recursao_abertos += pow_2(RECURSAO_MAX - 1) - 1;
        pthread_mutex_unlock(&mutex);
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
        pthread_mutex_lock(&mutex);
        soma_integral += integral_c;
        nos_recursao_fechados++;
        nos_recursao_abertos -= pow_2(RECURSAO_MAX - nivel_recursao);
        pthread_mutex_unlock(&mutex);
        return;
    }
    integral_recursiva(func, a, c, erro, nivel_recursao + 1);
    integral_recursiva(func, c, b, erro, nivel_recursao + 1);
}