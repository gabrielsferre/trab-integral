#ifndef _FUNCOES_H
#define _FUNCOES_H

#include <math.h>

/*
Header com a implementação das funções pedidas.
Elas estão na mesma ordem que a do enunciado do trabalho.
*/

#define PI 3.14159265358979323846
#define E_NUM 2.7182818284590452354 //Número de Euler

double func_a(double x) {
    return 1 + x;
}

double func_b(double x) {
    return sqrt(1 - x*x);
}

double func_c(double x) {
    return sqrt(1 + x*x*x*x);
}

double func_d(double x) {
    return sin(x*x);
}

double func_e(double x) {
    return cos(exp(-x));
}

double func_f(double x) {
    return cos(exp(-x)) * x;
}

double func_g(double x) {
    return cos(exp(-x)) * (0.005 * x*x*x + 1);
}
#endif