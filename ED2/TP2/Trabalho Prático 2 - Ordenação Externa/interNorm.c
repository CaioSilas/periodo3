#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "dados.h"
#include "ord_ext.h"
#include "interNorm.h"

void intercalacaoBase(FILE* ArqExterno, int qnt, Comp* resultado){
	clock_t tempo = clock(); //inicio do clock usado para contrar o tempo

	Fitas fitas;
	ItemArea aux;

	criaFitas(&fitas, 0); //criando previamente todas as fitas que serao usados
	blocoAleatorio(ArqExterno, &fitas, qnt, resultado); //Gera os blocos em todas as fitas

	double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    resultado[0].temp_exec = tempoCria; //colocando o tempo de execução da criacao

	tempo = clock();
		
	while(1){
		intercalacaoES(&fitas, qnt, resultado); //chama a funcao de intercalacao das fitas 0 a 19, para as fitas 20 a 39
		if(eFim(fitas, 1)){ //Se nao tem mais nada em nenhuma fita, a nao ser a 0 ou 20, libero as fitas antigas
			liberaFitas(&fitas, 1);
			criaFitas(&fitas, 1);
			resultado[1].valido = 0;
			break;
		}
		liberaFitas(&fitas, 1);
		criaFitas(&fitas, 1);
		intercalacaoSE(&fitas, qnt, resultado); //Processo semelhante ao citado acima, porem de 20 a 39 para 0 a 19
		if(eFim(fitas, 0)){
			liberaFitas(&fitas, -1);
			criaFitas(&fitas, -1);
			resultado[1].valido = 0;
			break;
		}
		liberaFitas(&fitas, -1);
		criaFitas(&fitas, -1);
	}

	double tempoOrdena = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    resultado[1].temp_exec = tempoOrdena; //Pegando o tempo apos a intercacao

	for(int i = 0; i < 2*f; i++){ //printando as fitas
		printf("Fita %d\n", i);
		fseek(fitas.fitas[i], 0, SEEK_SET);
		while (fread(&aux.reg, sizeof(Reg), 1, fitas.fitas[i])) {
			ImprimeRegistro(aux.reg);
		}
	}
	liberaFitas(&fitas, 0);
}

void blocoAleatorio(FILE* ArqExterno, Fitas* fitas, int qnt, Comp* resultado){
	int fitaEscrita = 0;
	Area area;
	ItemArea aux;
	area.tam = 0;


	while(fread(&aux.reg, sizeof(Reg), 1, ArqExterno)){ //Lendo um por um os registros do arquivo original
		resultado[0].num_transL++;
		resultado[0].num_comp += 3;
		insereArea(&area, aux); //Inserindo cada item na area de memoria interna
		if(area.tam == f){

			for(int i = 0; i < f; i++){
				resultado[0].num_comp += 5;
				aux = retiraArea(&area); //Depois que a area esta cheia, indo retirando um por um e colocando na fita que eles deve estar de saida
				fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
				resultado[0].num_transE++;
			}

			aux.reg.nota = -1; //Colocando um -1 que serve como separador entre nossos blocos
			fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
			resultado[0].num_transE++;
			fitas->tamFita[fitaEscrita]++;
			fitaEscrita++;
        	fitaEscrita %= f;
		}
	}
	int trocou = 0;
	while (area.tam != 0){ //Caso tenha saido do while de cima e ainda tenha sobrado itens (caso do ultimo bloco, que nao tem tamanho padrao)
		trocou = 1;
		
		resultado[0].num_comp += 5;
		aux = retiraArea(&area);
		fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
		resultado[0].num_transE++;
	}

	if(trocou == 1){
		aux.reg.nota = -1;
		fitas->tamFita[fitaEscrita]++;
		fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
		resultado[0].num_transE++;
	}
}
