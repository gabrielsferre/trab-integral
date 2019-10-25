#include "include/integral_sequencial.h"
#include <stdio.h>

static double my_abs(double n) {
    return n < 0 ? -n : n;
}

double integral_sequencial( double(*func)(double), double a, double b, double erro) {
    double c = (a+b)/2;    //ponto medio entre a e b
    double a_c = (a+c)/2;  //ponto medio entre a e c
    double c_b = (c+b)/2;  //ponto medio entre c e b
    double f_c = func(c);  //altura do retangulo com base ab 
    double f_a_c = func(a_c);  //altura do retangulo com base ac
    double f_c_b = func(c_b);  //altura do retangulo com base 
    double integral_c = f_c * (b - a);
    double integral_a_c = f_a_c * (a_c - a);
    double integral_c_b = f_c_b * (b - c_b);

    erro = my_abs(erro);
    if( my_abs( integral_c - (integral_a_c + integral_c_b) ) <= erro/10 ) {
        return integral_c;
    }
    return integral_sequencial(func, a, c, erro) + integral_sequencial(func, c, b, erro);
}