#ifndef INTERNORM_H
#define INTERNORM_H

#include "ord_ext.h"
#include "dados.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

//Funcao que controle o processo de intercacao
void intercalacaoBase(FILE* ArqExterno, int qnt, Comp* resultado);

//Funcao que gera os blocos normais
void blocoAleatorio(FILE* ArqExterno, Fitas* fitas, int qnt, Comp* resultado);

#endif