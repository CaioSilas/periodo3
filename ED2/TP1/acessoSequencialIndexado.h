#ifndef ACESSOSEQUENCIALINDEXADO_H
#define ACESSOSEQUENCIALINDEXADO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "dados.h"

#define ITENSPAGINA 4

void pesquisa(Indice* tabela, int tamanhoTabela, Reg* item, FILE* arquivo, Comp* resultado);
int acessoSequencialIndexado(FILE* arquivo, int quantidade, Reg* item, Comp* resultado);

#endif