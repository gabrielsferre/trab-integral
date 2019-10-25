#ifndef _INTEGRAL_SEQUENCIAL_H
#define _INTEGRAL_SEQUENCIAL_H

/*
Calcula a integral de 'func' no intervalo [a,b].

args:
    func: função que será integrada.
    a: primeiro valor do intervalo sobre o qual será calculada a integral
    b: segundo valor do intervalo sobre o qual será calculada a integral
    erro: erro absoluto admitido no valor numérico da integral

retorno:
    valor da integral calculado numericamente
*/
double integral_sequencial( double(*func)(double), double a, double b, double erro);

#endif