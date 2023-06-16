#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Include das structs gerais utilizadas
#include "gerador_arquivo.h"

//Include das structs gerais utilizadas
#include "dados.h"

//Include dos métodos de ORDENAÇÃO
#include "interNorm.h"
#include "ord_ext.h"
#include "quick.h"


int main(int argc, char **argv){

    FILE *ArqExterno;

    int metodo, qnt, situacao;

    //Começo das verificações

    if(argc != 5 && argc != 4){
        printf("Parametros de entrada invalidos.\n"
        "Ex: pesquisa <método> <quantidade> <situação> [-P]\n");
        return 0;
    }
    
    metodo = atoi(argv[1]);
    qnt = atoi(argv[2]);
    situacao = atoi(argv[3]);

    if(metodo < 1 || metodo > 3){
        printf("Parametro de entrada referente ao metodo invalido.\n"
        "<metodo>\n"
        "1 Intercalação balanceada de vários caminhos com formação de blocos com método básico\n"
        "2 Intercalação balanceada de vários caminhos com formação de blocos com método de seleção\n"
        "3 QuickSort\n");
        return 0;
    }

    if(situacao < 1 || situacao > 3){
        printf("Parametro de entrada referente a situacao invalido.\n"
        "<situacao>\n"
        "1 Arquivo Ordenado Ascendentemente\n"
        "2 Arquivo Ordenado Descendentemente\n"
        "3 Arquivo Desordenado Aleatoriamente\n");
        return 0;
    } 


    //Criando o arquivo Binário desejado a partir do PROVAO.TXT e suas versões ordenadas
        ArqExterno = gerador_arquivo(qnt, situacao);
        if(ArqExterno == NULL){
            printf("\n\nImpossivel abrir o arquivo registros.bin !!!!\n\n");
        return 0;
        }


    //Se o parâmetro -P for utilizado eu vou imprimir as chaves do arquivo que vou pesquisar
    if(argc != 4){
        if(strcmp(argv[4], "-P") != 0){
            printf("Parametro de entrada opicional invalido.\n"
            "<OP>\n"
            "-P é um argumento opicional para visualizar as chaves de pesquisa no arquivo\n");
        return 0;
        }
        else{
            Reg aux;
            for(int i = 0; i < qnt; i++){
                fread(&aux, sizeof(Reg), 1, ArqExterno);
                ImprimeRegistro(aux);
            }
            fseek(ArqExterno, 0, SEEK_SET);
        }
    }

    Comp resultado[2];
    resultado[0].num_comp = 0;
    resultado[0].num_transE = 0;
    resultado[0].num_transL = 0;
    resultado[0].temp_exec = 0;
    resultado[0].valido = 1;

    resultado[1].num_comp = 0;
    resultado[1].num_transE = 0;
    resultado[1].num_transL = 0;
    resultado[1].temp_exec = 0;
    resultado[1].valido = 1;



    //Chamo o método que for selecionado

    if(metodo == 1){
        intercalacaoBase(ArqExterno, qnt, resultado);
        if(resultado[1].valido != 0){
            printf("Não foi possível ordenar\n");
        }
    }

    if(metodo == 2){

        intercalacaoSelecao(ArqExterno, qnt, resultado);
        if(resultado[1].valido != 0){
            printf("Não foi possível ordenar\n");
        }
    }

    if(metodo == 3){
        char nome[25];
        if(situacao == 1){
            strcpy(nome,"crescente.bin");

        }
        else if(situacao == 2){
            strcpy(nome,"descedente.bin");

        }
        else {
            strcpy(nome,"aleatorio.bin");
        }
        
        inicia(nome,qnt,resultado);
        if(resultado[1].valido == 1){
            // ImprimeRegistro(registro);
        }
        else{
            printf("Não foi possível ordenar\n");
        }
    }


    //Apos realizar o método é imprimido o valor das tranferências e comparações junto com o tempo
    printf("\nPre processamento\n");
    printf("Escritas :%d\tLeituras %d\tComparacoes %d\tTempo de execucao %lf\n", resultado[0].num_transE, resultado[0].num_transL, resultado[0].num_comp, resultado[0].temp_exec);

    printf("\nOrdenacao\n");
    printf("Escritas :%d\tLeituras %d\tComparacoes %d\tTempo de execucao %lf\n", resultado[1].num_transE, resultado[1].num_transL, resultado[1].num_comp, resultado[1].temp_exec);

    fclose(ArqExterno);
    return 0;
}