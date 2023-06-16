#ifndef ARVOREBE_H
#define ARVOREBE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dados.h"

#ifndef ARVOREB_H
#define M 2

typedef long TipoChave;

typedef struct TipoRegistro{
    TipoChave chave;
}TipoRegistro;

typedef struct Indice {
    TipoChave chave;
    int posicaoArquivo;
} IndiceB;
#endif

typedef enum{
    Interna,
    Externa
} TipoNodo;

typedef struct TipoPaginaE* TipoApontadorE;

typedef struct TipoPaginaE{
    TipoNodo seletor;
    union {
        struct {
            int nInterno;
            int chavesInternas[2*M];
            TipoApontadorE descendentesInternos[2*M + 1];
        } Inter;
        struct {
            int nExterno;
            Reg registrosExternos[2*M];
        } Exter;
    } Paginas;
}TipoPaginaE;

void InicializaBE(TipoApontadorE Arvore);
void PesquisaBE(Reg *x, TipoApontadorE *Apontador, Comp *contagem);
void InsereNaPaginaInt(TipoApontadorE ApAtual, int Reg, TipoApontadorE ApDir, Comp *contagem);
void InsereNaPaginaExt(TipoApontadorE ApAtual, Reg Reg, Comp *contagem);
void InsBE(Reg Registro, TipoApontadorE Ap, int *Cresceu, Reg *RegRecursao, TipoApontadorE *ApRecursao, Comp *contagem);
void InsereBE(Reg Registro, TipoApontadorE *Ap, Comp *contagem);
// void ImprimeE(TipoApontadorE Arvore);
void ArvoreBE(FILE *arquivo, int qtd, Reg* registro, Comp* contagem);
void ImprimeReg(Reg registro);
void imprimeExterna(TipoApontadorE arv);


#endif