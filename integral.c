#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "../include/timer.h"

typedef double my_float;

my_float my_abs(my_float n) {
    return n < 0 ? -n : n;
}

my_float integral( my_float(*func)(my_float), my_float a, my_float b, my_float erro ) {
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
    if( my_abs( integral_c - (integral_a_c + integral_c_b) ) <= erro ) {
        return integral_c;
    }
    return integral(func, a, c, erro) + integral(func, c, b, erro);
}

int main() {
    double tempo, tempo_int;
    GET_TIME(tempo);
    my_float s = integral(cos, 0, 3.14159265359/2, 0.000001);
    GET_TIME(tempo_int);
    tempo_int = tempo_int - tempo;
    printf("%f\ntempo: %f\n", s, tempo_int);
}