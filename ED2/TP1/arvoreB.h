#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "dados.h"

#define M 5

typedef long TipoChave;

typedef struct TipoRegistro{
    TipoChave chave;
}TipoRegistro;

typedef struct Indice {
    TipoChave chave;
    int posicaoArquivo;
} IndiceB;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina{
    int n;
    IndiceB itens[2*M];
    TipoApontador descendentes[2*M + 1];
}TipoPagina;

void Inicializa(TipoApontador Arvore);
int Pesquisa(Reg* x, TipoApontador Apontador, Comp *contagem, FILE *arquivo);
void InsereNaPagina(TipoApontador ApAtual, IndiceB Reg, TipoApontador ApDir, Comp *contagem);
void Ins(IndiceB Registro, TipoApontador Ap, int *Cresceu, IndiceB *RegRecursao, TipoApontador *ApRecursao, Comp *contagem);
void Insere(IndiceB Registro, TipoApontador *Ap, Comp *contagem);
void Imprime(TipoApontador Arvore);
void ArvoreB(FILE *arquivo, int qtd, Reg* registro, Comp* contagem);
void ImprimeReg(Reg registro);

#endif