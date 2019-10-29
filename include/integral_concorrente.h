#ifndef _INTEGRAL_CONCORRENTE_H
#define _INTEGRAL_CONCORRENTE_H

#include "../include/conc_util.h"
#include "../include/integral_sequencial.h"

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
double integral_concorrente( double(*func)(double), double a, double b, double erro, int n_threads );

#endif
