#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 10

typedef int tipo_fila;

typedef struct {
    tipo_fila* vec;
    int inicio;
    int fim;
    int tamanho;
    int n_elementos;
} Fila;

void init_fila(Fila *fila) {
    fila->vec = (tipo_fila*)malloc(sizeof(tipo_fila) * TAM_INICIAL);
    fila->tamanho = TAM_INICIAL;
    fila->n_elementos = 0;
    fila->inicio = 0;
    fila->fim = 0;
}

static void overflow_fila(Fila *fila) {
    int novo_tamanho = 2 * fila->tamanho;
    tipo_fila* novo_vec = (tipo_fila*)malloc(sizeof(tipo_fila) * novo_tamanho);
    
    for(int i = fila->tamanho - 1; i >= 0; i--) {
        novo_vec[i] = fila->vec[fila->inicio];
        fila->inicio = (fila->inicio + 1) % fila->tamanho;
    }
    
    fila->inicio = 0;
    fila->fim = fila->tamanho;
    fila->tamanho = 
}

void print_fila(tipo_fila* fila, int tam) {
    for( int i = 0; i < tam; i++ ) {
        printf("%d ", fila[i]);
    }
    printf("\n");
}

int main()
{

    return 0;
}
