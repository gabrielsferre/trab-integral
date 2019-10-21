#include "include/integral_sequencial.h"
#include <stdio.h>
static my_float my_abs(my_float n) {
    return n < 0 ? -n : n;
}

my_float integral_sequencial( my_float(*func)(my_float), my_float a, my_float b, my_float erro) {
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
        return integral_c;
    }
    return integral_sequencial(func, a, c, erro) + integral_sequencial(func, c, b, erro);
}