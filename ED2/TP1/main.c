#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Include das structs gerais utilizadas
#include "dados.h"

//Include dos métodos de pesquisa
#include "acessoSequencialIndexado.h"
#include "arq_binary.h"
#include "arvoreB.h"
#include "arvoreBE.h"


//Definindo valor máximo de pesquisa
#define MILHAO 1000000

int main(int argc, char **argv){

    FILE *ArqExterno;

    int metodo, qnt, situacao, chave;

    //Começo das verificações

    if(argc != 6 && argc != 5){
        printf("Parametros de entrada invalidos.\n"
        "Ex: pesquisa <método> <quantidade> <situação> <chave> [-P]\n");
        return 0;
    }
    
    metodo = atoi(argv[1]);
    qnt = atoi(argv[2]);
    situacao = atoi(argv[3]);
    chave = atoi(argv[4]);

    if(metodo < 1 || metodo > 4){
        printf("Parametro de entrada referente ao metodo invalido.\n"
        "<metodo>\n"
        "1 Acesso Sequencial Indexado\n"
        "2 Arvore Binaria de Pesquisa Externa\n"
        "3 Arvore B\n"
        "4 Arvore B*\n");
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

    //Dependendo da ordenação que for escolhida eu abro 1 entre 3 arquivos diferentes

    if(situacao == 1){
        ArqExterno = fopen("registros_cres.bin", "rb");
        if(ArqExterno == NULL){
            printf("\n\nImpossivel abrir o arquivo registros.bin !!!!\n\n");
        return 0;
        }
    }

    else if(situacao == 2){
        ArqExterno = fopen("registros_decres.bin", "rb");
        if(ArqExterno == NULL){
            printf("\n\nImpossivel abrir o arquivo registros.bin !!!!\n\n");
        return 0;
        }
    }

    else if(situacao == 3){
        ArqExterno = fopen("registros_aleatorio.bin", "rb");
        if(ArqExterno == NULL){
            printf("\n\nImpossivel abrir o arquivo registros.bin !!!!\n\n");
        return 0;
        }
    }

    if(chave == 0 && strcmp(argv[4], "0") != 0){    
        printf("Parametro de entrada referente a chave invalido.\n"
        "<chave>\n"
        "O valor da chave de registror que voce pode pesquisar esta entre 0 e 999.999\n");
            return 0;
    }
    if(chave < 0){
        printf("Parametro de entrada referente a chave invalido.\n"
        "<chave>\n"
        "O valor da chave de registror que voce pode pesquisar esta entre 0 e 999.999\n");
        return 0;
    }
    //Se o parâmetro -P for utilizado eu vou imprimir as chaves do arquivo que vou pesquisar
    if(argc != 5){
        if(strcmp(argv[5], "-P") != 0){
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

    

    Reg registro;
    Comp resultado[2];

    //Chamo o método que for selecionado

    registro.chave = chave;
    if(metodo == 1){
        acessoSequencialIndexado(ArqExterno, qnt, &registro, resultado);
        if(resultado[1].valido == 0){
            ImprimeRegistro(registro);
        }
        else{
            printf("Não foi possível encontrar o registro\n");
        }
    }

    if(metodo == 2){
        ArvoreExterna(ArqExterno, qnt, &registro, resultado);
        if(resultado[1].valido == 0){
            ImprimeRegistro(registro);
        }
        else{
            printf("Não foi possível encontrar o registro\n");
        }
    }

    if(metodo == 3){
        ArvoreB(ArqExterno, qnt, &registro, resultado);
        if(resultado[1].valido == 1){
            ImprimeRegistro(registro);
        }
        else{
            printf("Não foi possível encontrar o registro\n");
        }
    }

    if(metodo == 4){
        ArvoreBE(ArqExterno, qnt, &registro, resultado);
        if(resultado[1].valido == 1){
            ImprimeRegistro(registro);
        }
        else{
            printf("Não foi possível encontrar o registro\n");
        }

    }

    //Apos realizar o método é imprimido o valor das tranferências e comparações junto com o tempo

    printf("\nCriação\n");
    printf("Tranferencias :%d\tComparacoes %d\tTempo de execucao %lf\n", resultado[0].num_trans, resultado[0].num_comp, resultado[0].temp_exec);

    printf("\nPesquisa\n");
    printf("Tranferencias :%d\tComparacoes %d\tTempo de execucao %lf\n", resultado[1].num_trans, resultado[1].num_comp, resultado[1].temp_exec);

    fclose(ArqExterno);

    return 0;
}