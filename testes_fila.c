#include "include/fila.h"

//Teste bobo e um tanto precário para fila.
//Quando for testar, mudar o tipo da fila no fila.h para int

int main()
{
    Fila fila;
    fila_init(&fila);    
    fila_insere(&fila, 1); fila_print(fila);
    fila_insere(&fila, 2); fila_print(fila);
    fila_insere(&fila, 3); fila_print(fila);
    fila_insere(&fila, 4); fila_print(fila);
    fila_remove(&fila); fila_print(fila);
    fila_insere(&fila, 5); fila_print(fila);
    fila_insere(&fila, 6); fila_print(fila);
    fila_insere(&fila, 7); fila_print(fila);
    fila_insere(&fila, 8); fila_print(fila);
    fila_insere(&fila, 9); fila_print(fila);
    fila_insere(&fila, 10); fila_print(fila);
    fila_remove(&fila); fila_print(fila);
    fila_remove(&fila); fila_print(fila);
    fila_remove(&fila); fila_print(fila);

    fila_delete(&fila);
    return 0;
}