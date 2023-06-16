#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"
#include "ord_ext.h"

FILE* gerador_arquivo(int n, int tipo){

    FILE *arq;
    if(tipo == 1){
        arq = fopen("PROVAO_ASCENDENTE.txt", "r");
        if(arq == NULL){
            return 0;
        }
    }

    else if(tipo == 2){
        arq = fopen("PROVAO_DESCENDENTE.txt", "r");
        if(arq == NULL){
            return 0;
        }
    }

    else {
        arq = fopen("PROVAO.TXT", "r");
        if(arq == NULL){
            return 0;
        }
    }

    FILE *insere = NULL;

    Reg reg;
    char vector[102];
    if(tipo == 1){
        insere = fopen("crescente.bin", "w+b");
    }
    else if(tipo == 2){
        insere = fopen("descedente.bin", "w+b");
    }
    else{
        insere = fopen("aleatorio.bin", "w+b");
    }

    for(int i = 0; i < n; i++){
        fgets(vector, 102, arq);
        
        reg.numInscr = atoi(vector);
        reg.nota = atof(vector+8);      
        reg.estado[0] = vector[15]; reg.estado[1] = vector[16]; reg.estado[2] = '\0';
        for(int j = 18; j < 68; j++){
            reg.cidade[j - 18] = vector[j]; 
        }
        reg.cidade[50] = '\0';
        for(int j = 69; j < 99; j++){
            reg.curso[j - 69] = vector[j]; 
        }
        reg.curso[30] = '\0';

        fwrite(&reg, sizeof(Reg), 1 , insere);

    }
    
    fseek(insere, 0, SEEK_SET);
    fclose(arq);

    return insere;
}
