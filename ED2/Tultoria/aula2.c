//caio silas
//21.1.4111

#include<stdbool.h>
#include<stdio.h>

#define M 2

typedef long TipoChave;
typedef struct TipoRegistro {
    TipoChave Chave;
    /* outros componentes */
} TipoRegistro;
typedef struct TipoPagina* TipoApontador;
typedef struct TipoPagina {
    short n;
    TipoRegistro r[M*2];
    TipoApontador p[M*2 + 1];
}TipoPagina;

bool pesquisa(TipoRegistro *x,TipoApontador Ap){
    long i;
    if (Ap == NULL){
        return false;
    }

    while(i < Ap->n && x->Chave > Ap->r[i - 1].Chave) i++;

    if (x->Chave == Ap->r[i -1].Chave){
        *x = Ap->r[i - 1];
        return true;
    }

    if (x->Chave < Ap->r[i - 1].Chave){
        pesquisa(x, Ap->p[i- 1]);
    }
    else pesquisa(x, Ap->p[i]);
}

void minimo(TipoRegistro *x, TipoApontador Ap){
    int i = 0;

    if (Ap->p[0] == NULL){
        *x = Ap->r[0];
        return;
    }
    minimo(x,Ap->p[0]);
}

void Max (TipoRegistro *x, TipoApontador Ap){
    if (Ap->p[1] == NULL){
        *x = Ap->r[1];
        return;
    }
    Max(x,Ap->p[1]);
}

