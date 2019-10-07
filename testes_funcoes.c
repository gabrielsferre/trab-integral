#include <stdio.h>
#include "funcoes.h"

void teste(my_float(*func)(my_float), my_float arg, my_float resultado_esperado, my_float erro, const char nome_teste[]) {
    my_float resultado = func(arg);
    erro = my_abs(erro);
    if( my_abs(resultado - resultado_esperado) > erro ) {
        printf("Erro no teste %.64s\n", nome_teste);
        printf("Resultado esperado: %.10f\n", resultado_esperado);
        printf("Resultado encontrado: %.10f\n\n", resultado);
    }
}



int main() {
    return 0;
}