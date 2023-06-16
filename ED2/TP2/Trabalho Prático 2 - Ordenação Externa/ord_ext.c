#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "dados.h"
#include "ord_ext.h"

//Função principal que faz a intercalação por substituição
void intercalacaoSelecao(FILE* ArqExterno, int qnt, Comp* resultado){
    clock_t tempo = clock();
	
	Fitas fitas;
	ItemArea aux;
	
	//Crio as fitas e realizo a seleção por substituição
	criaFitas(&fitas, 0);
	blocoSelecao(ArqExterno, &fitas, qnt, resultado);
	
	double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    resultado[0].temp_exec = tempoCria;

    tempo = clock();

	//Chamo a intercalação em recursão
	while(1){
		//Chamo a intercalação de saída pra entrada e libero as fitas que eu intercalei
		intercalacaoES(&fitas, qnt, resultado);
		
		//Se a intercalação acabar eu paro o while e valido a ordenação
		if(eFim(fitas, 1)){
			liberaFitas(&fitas, 1);
			criaFitas(&fitas, 1);
			resultado[1].valido = 0;
			break;
		}
		liberaFitas(&fitas, 1);
		criaFitas(&fitas, 1);
		
		//Chamo a intercalação de entrada pra saída e libero as fitas que eu intercalei
		intercalacaoSE(&fitas, qnt, resultado);
		//Se a intercalação acabar eu paro o while e valido a ordenação
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
    resultado[1].temp_exec = tempoOrdena;

	//Imprimo as fitas
	for(int i = 0; i < 2*f; i++){
		printf("Fita %d\n", i);
		fseek(fitas.fitas[i], 0, SEEK_SET);
		while (fread(&aux.reg, sizeof(Reg), 1, fitas.fitas[i])) {
			ImprimeRegistro(aux.reg);
		}
	}


	liberaFitas(&fitas, 0);
}

//Função que faz a intercalação das fitas de entrada pras fitas de saída
void intercalacaoES(Fitas* fitas, int qnt, Comp* resultado){

	int fitaEscrita = f;
	int acabou[f]; // acabou bloco
	int blocosLidos[f];

	Area area;
	area.tam = 0;
	area.ultimo = INT_MIN;

	//Volto o ponteiro dos arquivos ao começo
	ItemArea aux;
	for(int i = 0; i < 2*f; i++){
		fseek(fitas->fitas[i], 0, SEEK_SET);		
	}

	//Reseto os vetores auxiliares
	for(int i = 0; i < f; i++){
		acabou[i] = 0;
		blocosLidos[i] = 0;
	}

	int k = 0;
	
	while(temBloco(fitas, blocosLidos, 0, f)){
		area.ultimo = INT_MIN;
		k++;
		//Leio os 20 primeiros elementos de cada fita
		for(int i = 0; i < 20; i++){
			resultado[1].num_transL++;
			fread(&aux.reg, sizeof(Reg), 1, fitas->fitas[i]);
			if(feof(fitas->fitas[i])){
				break;
			}
			aux.flag = 0;
			aux.fita = i;

			resultado[1].num_comp += 3;
			insereArea(&area, aux);
		}

		for(int i = 0; i < f; i++){
			acabou[i] = 0;
		}

	
		while(area.tam != 0){
			//Retiro a raiz do Heap e insiro no arquivo
			resultado[1].num_comp += 5;
			aux = retiraArea(&area);

			resultado[1].num_transE++;
			fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);

			//Se ainda tiver elemento pra ler eu continuo
			if(!acabou[aux.fita] && blocosLidos[aux.fita] < fitas->tamFita[aux.fita]){
				resultado[1].num_transL++;
				fread(&aux.reg, sizeof(Reg), 1, fitas->fitas[aux.fita]);

				if(aux.reg.nota < 0){
					acabou[aux.fita] = 1;
					blocosLidos[aux.fita]++;
				}
				else{
					resultado[1].num_comp += 3;
					insereArea(&area, aux);
				}
			}

			//Se acabar os blocos eu troco de fita
			if(todasCheias(area)){
				for(int j = 0; j < 20; j++){
					area.iArea[j].flag = 0;
				}
				aux.reg.nota = -1;
				fitas->tamFita[fitaEscrita]++;
				resultado[1].num_transE++;
				fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);

				//Transformando a fita escrita
				fitaEscrita++;
				fitaEscrita %= f;
				fitaEscrita += f;
			}
		}
	}
}

//Função que faz a intercalação das fitas de entrada pras fitas de saída
void intercalacaoSE(Fitas* fitas, int qnt, Comp* resultado){
	//Esta função é semelhante à outra porém com pequenas diferencias


	int fitaEscrita = 0;
	int acabou[f]; // acabou bloco
	int blocosLidos[f];

	Area area;
	area.tam = 0;
	area.ultimo = INT_MIN;

	
	ItemArea aux;
	for(int i = 0; i < 2*f; i++){
		fseek(fitas->fitas[i], 0, SEEK_SET);		
	}

	for(int i = 0; i < f; i++){
		acabou[i] = 0;
		blocosLidos[i] = 0;
	}

	int k = 0;
	
	while(temBloco(fitas, blocosLidos, f, 2 * f)){
		area.ultimo = INT_MIN;
		k++;
		for(int i = f; i < 2 * f; i++){
			resultado[1].num_transL++;
			fread(&aux.reg, sizeof(Reg), 1, fitas->fitas[i]);
			if(feof(fitas->fitas[i])){
				break;
			}
			aux.flag = 0;
			aux.fita = i;
			resultado[1].num_comp += 3;
			insereArea(&area, aux);
		}

		for(int i = 0; i < f; i++){
			acabou[i] = 0;
		}

	
		while(area.tam != 0){
			resultado[1].num_comp += 5;
			aux = retiraArea(&area);

			resultado[1].num_transE++;
			fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);

			if(!acabou[aux.fita % f] && blocosLidos[aux.fita % f] < fitas->tamFita[aux.fita]){
				resultado[1].num_transL++;
				fread(&aux.reg, sizeof(Reg), 1, fitas->fitas[aux.fita]);
			
				if(aux.reg.nota < 0){
					acabou[aux.fita % f] = 1;
					blocosLidos[aux.fita % f]++;
				}
				else{
					resultado[1].num_comp += 3;
					insereArea(&area, aux);
				}
			}

			if(todasCheias(area)){
				for(int j = 0; j < 20; j++){
					area.iArea[j].flag = 0;
				}
				aux.reg.nota = -1;
				fitas->tamFita[fitaEscrita]++;
				resultado[1].num_transE++;
				fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);

				//Transformando a fita escrita
				fitaEscrita++;
				fitaEscrita %= f;
			}
		}
	}
}

//Função que confere se existe blocos para serem lidos ainda
int temBloco(Fitas* fitas, int* blocosLidos, int begin, int end){
	for(int i = begin; i < end; i++){
		if(blocosLidos[i- begin] != fitas->tamFita[i]){
			return 1;
		}
	}
	return 0;
}

//Função que confere se existe elementos para serem lidos ainda
int temElemento(int* acabou){
	
	for(int i = 0; i < f; i++){
		if(acabou[i] == 0){
			return 1;
		}
	}
	return 0;
}

//Função que popula os blocos
void blocoSelecao(FILE* ArqExterno, Fitas* fitas, int qnt, Comp* resultado){
	int fitaEscrita = 0;
	Area area;
	ItemArea aux;
	area.tam = 0;
	area.ultimo = INT_MIN;

	//Função que pega os 20 primeiros elementos do arquivo
	for(int i = 0; i < 20; i++){
		
		resultado[0].num_transL++;
		fread(&aux.reg, sizeof(Reg), 1, ArqExterno);
		aux.flag = 0;
		if(feof(ArqExterno)){
			break;
		}

		resultado[0].num_comp += 3;
		insereArea(&area, aux);
	}

	resultado[0].num_comp += 5;
	aux = retiraArea(&area);

	resultado[0].num_transE++;
	fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);

	//Depois de popular a area você pega de 1 em 1 até a quantidade desejada
	for(int i = 20; i < qnt; i++){
		resultado[0].num_transL++;
		fread(&aux.reg, sizeof(Reg), 1, ArqExterno);
		aux.flag = 0;

		resultado[0].num_comp += 3;
		insereArea(&area, aux);
		//Verifica se os blocos estão cheios
		if(todasCheias(area)){
			for(int j = 0; j < 20; j++){
				area.iArea[j].flag = 0;
			}
			//Vamos mudar de fita então para delimitar o tamanho insiro um elemento com -1
			aux.reg.nota = -1;
			fitas->tamFita[fitaEscrita]++;
			resultado[0].num_transE++;
			fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
			
			fitaEscrita++;
			fitaEscrita %= f;
		}

		resultado[0].num_comp += 5;
		aux = retiraArea(&area);
		resultado[0].num_transE++;
		fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
	
	}
	int trocouFita = 0;
	Reg aux2;

	//While serve para colocar resto de blocos 
	while(area.tam > 0){
		resultado[0].num_comp += 5;
		aux = retiraArea(&area);
		if (aux.flag == 1 && !trocouFita) {

			aux2 = aux.reg;
			aux2.nota = -1;
			fitas->tamFita[fitaEscrita]++;
			resultado[0].num_transE++;
			fwrite(&(aux2), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
			
			fitaEscrita++;
			trocouFita = 1;
		}
		resultado[0].num_transE++;
		fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);
	}
	//-1 para identificar o fim de blocos
	aux.reg.nota = -1;
	fitas->tamFita[fitaEscrita]++;
	resultado[0].num_transE++;
	fwrite(&(aux.reg), sizeof(Reg), 1, fitas->fitas[fitaEscrita]);

}

//Vendo se so existe um bloco, na fita 0 ou 20
int eFim(Fitas fitas, int t){ 
	if(t == 1){
		t = f;
	}
	for(int i = t+1; i < f + t; i++){
		if(fitas.tamFita[i] !=0){
			return 0;
		}
	}

	return 1;
}

//Vendo se a area esta cheia
int todasCheias(Area area){ 
	for(int i = 0; i < area.tam; i++){
		if(area.iArea[i].flag == 0){
			return 0;
		}
	}
	return 1;
}

//Função que retira a raiz do Heap e refaz a propriedade do mesmo
ItemArea retiraArea(Area* area){
	ItemArea aux;

	if(area->tam == 0){
		aux.reg.nota = -1;
		aux.fita = -1;
		printf("Nao existe elemento na Area\n");
		return aux;
	}

	aux = area->iArea[0];

	Troca(area->iArea, 0, area->tam-1);
	area->tam--;
	area->ultimo = aux.reg.nota;

	Heap_Remake(area->iArea, 0, area->tam - 1);
	return aux;
}

//Função que insere um elemento na área e verifica se ele é menor que o último elemento retirado
void insereArea(Area* area, ItemArea item){
	if(item.reg.nota < area->ultimo){
		item.flag = 1;
	}
	area->iArea[area->tam] = item;
	area->tam++;
	
	Heap_RemakeEnd(area->iArea, 0, area->tam - 1);
}

//Função que cria fitas de maneira total ou parcial
void criaFitas(Fitas* fitas, int t){
	if(t == 0){
		for(int i = 0; i < 2*f; i++){
			char arq[10];
			snprintf(arq, 10, "f_%d.bin", i);
			fitas->fitas[i] = fopen(arq, "w+b");
			fitas->tamFita[i] = 0;
		}
	}

	else if (t == 1){
		t = f;
		for(int i = t-f; i < t; i++){
			char arq[10];
			snprintf(arq, 10, "f_%d.bin", i);
			fitas->fitas[i] = fopen(arq, "w+b");
			fitas->tamFita[i] = 0;
		}
	}

	else{
		t = 2*f;
		for(int i = t-f; i < t; i++){
			char arq[10];
			snprintf(arq, 10, "f_%d.bin", i);
			fitas->fitas[i] = fopen(arq, "w+b");
			fitas->tamFita[i] = 0;
		}
	}	
}

//Função que libera as fitas de maneira total ou parcial
void liberaFitas(Fitas* fitas, int t){
	if(t == 0){
		for(int i = 0; i < 2*f; i++){
			fclose(fitas->fitas[i]);
		}
	}

	else if (t == 1){
		t = f;
		for(int i = t-f; i < t; i++){
			fclose(fitas->fitas[i]);
		}
	}

	else{
		t = 2*f;
		for(int i = t-f; i < t; i++){
			fclose(fitas->fitas[i]);
		}
	}	
}

//Função que troca 2 elementos em uma área
void Troca(ItemArea *ordena, int i, int j){
	ItemArea aux = ordena[i];
	ordena[i] = ordena[j];
	ordena[j] = aux;
}

//Função que compara dois elementos em uma área
int Compara(ItemArea valor1, ItemArea valor2){
	if(valor1.flag == valor2.flag){
		if(valor1.reg.nota >= valor2.reg.nota){
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		if(valor1.flag != 0){
			return 0;
		}
		else{
			return 1;
		}
	}
	
}

//Heap_Remake padrão
void Heap_Remake(ItemArea *vetor, int esq, int dir){
	int pai = esq;
	int filho = pai*2+1;
	ItemArea aux = vetor[pai];
	
	while(filho <= dir){
		if(filho < dir && Compara(vetor[filho], vetor[filho+1]) == 0){
			filho++;
		}
		if(Compara(aux, vetor[filho]) == 1){
			break;
		}

		vetor[pai] = vetor[filho];
		pai = filho;
		filho = pai*2 +1;
	}

	vetor[pai] = aux;
}

//Heap_Remake alterada
void Heap_RemakeEnd(ItemArea *vetor, int esq, int dir) {
	int i = esq;
	int j = dir;
	ItemArea aux;

	while (j > i) {
		int pai = (j-1)/2;
		if (Compara(vetor[pai], vetor[j]) == 0) {
			aux = vetor[pai];
			vetor[pai] = vetor[j];
			vetor[j] = aux;
		}

		j = pai;
	}
}

void ImprimeRegistro(Reg registro){
	printf("\n%08ld %05.1lf %s %s %s\n", registro.numInscr , registro.nota, registro.estado, registro.cidade, registro.curso);
}
