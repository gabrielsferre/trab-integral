#include "fila.h"

//Teste bobo e um tanto precário para fila.
//Quando for testar, mudar o tipo da fila no fila.h para int

int main()
{
    Fila fila;
    init_fila(&fila);    
    insere_fila(&fila, 1); print_fila(fila);
    insere_fila(&fila, 2); print_fila(fila);
    insere_fila(&fila, 3); print_fila(fila);
    insere_fila(&fila, 4); print_fila(fila);
    remove_fila(&fila); print_fila(fila);
    insere_fila(&fila, 5); print_fila(fila);
    insere_fila(&fila, 6); print_fila(fila);
    insere_fila(&fila, 7); print_fila(fila);
    insere_fila(&fila, 8); print_fila(fila);
    insere_fila(&fila, 9); print_fila(fila);
    insere_fila(&fila, 10); print_fila(fila);
    remove_fila(&fila); print_fila(fila);
    remove_fila(&fila); print_fila(fila);
    remove_fila(&fila); print_fila(fila);

    delete_fila(&fila);
    return 0;
}