#ifndef QUICK_h
#define QUICK_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMAREA 20
#include "dados.h"


typedef int TipoApontador;

typedef int TipoRegistro;


typedef struct {
    Reg vector[TAMAREA];
    int quant;
}TipoArea;



void selectionsort(TipoArea *Area,Comp *resultado);
void IsereItem(Reg *UltLido,TipoArea *Area);
void RetiraPrimeiro(TipoArea *Area,Reg *R);
void RetiraUltimo(TipoArea *Area,Reg *R);
int ObeterNumCelOcupadas(TipoArea *Area);
void quickSorteExterno (FILE **ArqLi, FILE **ArqEI, FILE **ArqLEs, int Esq, int Dir,Comp *resultado);
void FAVazia(TipoArea *Area);
void LeSup(FILE **ArqLEs, Reg *UltLido, int *Ls, bool *OndeLer,Comp *resultado);
void Leinf(FILE **ArqLi,Reg *UltLido,int *Li, bool *OndeLer,Comp *resultado);
void InserirArea(TipoArea *Area, Reg *UltLido,int *NRArea,Comp *resultado);
void EscreveMax(FILE **ArqLEs,Reg R, int *Es,Comp *resultado);
void EscreveMin(FILE **ArqEI,Reg R, int *Ei,Comp *resutado);
void RetiraMax(TipoArea *Area,Reg *R, int *NRArea);
void RetiraMin(TipoArea *Area,Reg *R,int *NRArea);
void Particao(FILE **ArqLi,FILE **ArqEI,FILE **ArqLEs,TipoArea Area,int Esq, int Dir,int *i,int *j,Comp *resultado);
void inicia(char *nome,int qnt,Comp *resultado );



#endif