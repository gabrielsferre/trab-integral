#ifndef _INTEGRAL_SEQUENCIAL_H
#define _INTEGRAL_SEQUENCIAL_H

typedef double my_float;

/*
Calcula a integral de 'func' no intervalo [a,b].

args:
    func: função que será integrada. Deve ser uma função de uma variável.
    a: primeiro valor do intervalo sobre o qual será calculada a integral
    b: segundo valor do intervalo sobre o qual será calculada a integral
    erro: erro absoluto admitido no valor numérico da integral

retorno:
    valor da integral calculado numericamente
*/
my_float integral_sequencial( my_float(*func)(my_float), my_float a, my_float b, my_float erro);

#endif