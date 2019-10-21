#ifndef _FILA_H
#define _FILA_H 

#include "include/conc_util.h"

/*
Implementação de uma fila, usada para o cálculo concorrente da integral. 
*/

#define TAM_INICIAL 8

typedef int tipo_fila;

typedef struct {
    tipo_fila* vec;
    int inicio;
    int fim;
    int tamanho;
    int n_elementos;
} Fila;

static void fila_init(Fila *fila) {
    fila->vec = (tipo_fila*)Malloc(sizeof(tipo_fila) * TAM_INICIAL);
    fila->tamanho = TAM_INICIAL;
    fila->n_elementos = 0;
    fila->inicio = 0;
    fila->fim = 0;
}

static void fila_delete(Fila *fila) {
    free(fila->vec);
}

static void fila_overflow(Fila *fila) {
    int novo_tamanho = 2 * fila->tamanho;
    tipo_fila* novo_vec = (tipo_fila*)Malloc(sizeof(tipo_fila) * novo_tamanho);
    
    for(int i = 0; i < fila->tamanho; i++) {
        novo_vec[i] = fila->vec[fila->inicio];
        fila->inicio = (fila->inicio + 1) % fila->tamanho;
    }

    free(fila->vec);

    fila->inicio = 0;
    fila->fim = fila->tamanho;
    fila->tamanho = novo_tamanho;
    fila->vec = novo_vec;
}

static void fila_insere(Fila *fila, tipo_fila elemento) {
    if( fila->n_elementos == fila->tamanho) {
        overflow_fila(fila);
    }

    fila->vec[fila->fim] = elemento;
    fila->fim = (fila->fim + 1) % fila->tamanho;
    fila->n_elementos++;
}

static tipo_fila fila_remove(Fila *fila) {
    if(fila->n_elementos == 0) {
        printf("fila.h :: Tentando retirar elemento de fila vazia\n");
        return fila->vec[0];
    }
    
    tipo_fila elemento_retirado = fila->vec[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
    fila->n_elementos--;
    return elemento_retirado;
}

static void fila_print(Fila fila) {
    int iter = fila.inicio;
    for( int i = 0; i < fila.n_elementos; i++ ) {
        printf("%d ", fila.vec[iter]);
        iter = (iter + 1) % fila.tamanho;
    }
    printf("\n");
}
#endif
