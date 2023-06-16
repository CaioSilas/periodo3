#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dados.h"
#include "arq_binary.h"


void ArvoreExterna(FILE *arq, int qnt, Reg *registro, Comp* resultado){
    clock_t tempo = clock();
    //Variaveis auxiliares que me ajudam a trocar as informações no arquivo
    Reg aux;
    Indice index;
    
    //Caso base se o arquivo não funcionar
    FILE *arvore = fopen("arvore.bin", "w+b");
    if(arvore == NULL){
        printf("\n\nImpossivel criar o arquivo arvore.bin !!!!\n\n");
    }
    //Variavel flag pra verificar se foi possível ou não inserir na árvore
    resultado[0].num_comp = 0;
    resultado[0].num_trans = 0;

    resultado[1].num_comp = 0;
    resultado[1 ].num_trans = 0;
    //No for a seguir eu leio um elemento do arquivo e insiro ele na árvore binária
    for(int i = 0; i < qnt; i++){

        fread(&aux, sizeof(Reg), 1, arq);
        resultado[0].num_trans++;
        index.chave = aux.chave;
        index.posicaoArq = i;
        fseek(arvore, 0, SEEK_SET);
        
        Comp temp1 = InsertArvoreExterna(arvore, index);
        resultado[0].num_comp += temp1.num_comp;
        resultado[0].num_trans += temp1.num_trans;
        resultado[0].valido = temp1.valido;
        // //Se o resultado for 1 já existe um elemento com a mesma chave e paro o programa
        if(resultado[0].valido == 1){
            return;
        }
    }
    double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    resultado[0].temp_exec = tempoCria;

    tempo = clock();
    //Após a busca eu retorno o ponteiro para o começo para realizar a busca no registro desejado pelo usuário
    fseek(arvore, 0, SEEK_SET);

    Comp temp2 = SearchArvoreExterna(arvore, registro->chave, &index);
    resultado[1].num_comp += temp2.num_comp;
    resultado[1].num_trans += temp2.num_trans;
    resultado[1].valido = temp2.valido;

    //Utilizando a posicaoArq do index eu encontro diretamente no arquivo o elemento que estava na árvore
    fseek(arq, index.posicaoArq*sizeof(Reg), SEEK_SET);
    fread(registro, sizeof(Reg), 1, arq);

    double tempoPesq = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    resultado[1].temp_exec = tempoPesq;     

    fclose(arvore);
    return;

}

Comp InsertArvoreExterna(FILE *arq, Indice index){
    Comp conta;
    conta.num_comp = 0;
    conta.num_trans = 0;

    ArvoreExt aux;
    //Verifico se a árvore é vazia
    int tamArq = fread(&aux, sizeof(ArvoreExt), 1, arq);
    conta.num_trans++;
    
    //Começo o valor que vou inserir na árvore
    ArvoreExt inserido;
    inserido.indice = index;
    inserido.F_dir = -1;
    inserido.F_esq = -1;


    //Se a arvore for vazia eu vou inserir sem acessar ela recursivamente
    if(tamArq == 0){
        fwrite(&inserido, sizeof(ArvoreExt), 1, arq);
        return conta;
    }

    //Se o elemento existir eu retorno que já existe o valor
    if(aux.indice.chave == index.chave){
        conta.num_comp++;
        conta.valido = 1;
        return conta;
    }

    //Se não for possível nenhum das opções de cima
    //Vou acessar os filhos apartir da propriedade da árvore do filho a direita ser maior que o pai
    //E o da esquerda ser menor

    //Como é uma arquivo eu dou fseek utilizando a posição no arquivo do filho do pai
    if(aux.indice.chave > index.chave && aux.F_esq != -1){
        fseek(arq, aux.F_esq*sizeof(ArvoreExt), SEEK_SET);
        conta.num_comp++;

        Comp temp = InsertArvoreExterna(arq, index);
        conta.num_trans += temp.num_trans;
        conta.num_comp += temp.num_comp;
        conta.valido = temp.valido;

        return conta;   
    }
    if(aux.indice.chave < index.chave && aux.F_dir != -1){
        fseek(arq, aux.F_dir*sizeof(ArvoreExt), SEEK_SET);
        conta.num_comp++;

        Comp temp = InsertArvoreExterna(arq, index);
        conta.num_trans += temp.num_trans;
        conta.num_comp += temp.num_comp;
        conta.valido = temp.valido;

        return conta;
    }
    //salvo a posição do pai
    int tmp = ftell(arq)/sizeof(ArvoreExt) - 1;
    fseek(arq, 0, SEEK_END);


    //Se o pai não conter filhos validos você insere o elemento como filho
    if(aux.indice.chave > index.chave){
        conta.num_comp++;
        aux.F_esq = ftell(arq)/sizeof(ArvoreExt);
    }
    else{
        conta.num_comp++;
        aux.F_dir = ftell(arq)/sizeof(ArvoreExt);
    }

    fwrite(&inserido, sizeof(ArvoreExt), 1, arq);

    //Atualizo o filho do pai como o novo elemento inserido
    fseek(arq, tmp*sizeof(ArvoreExt), SEEK_SET);
    fwrite(&aux, sizeof(ArvoreExt), 1, arq);

    return conta;
}

Comp SearchArvoreExterna(FILE *arq, int chave, Indice *index){
    //A busca binária utiliza a mesma ideia da inserção
    
    Comp conta;
    conta.num_comp = 0;
    conta.num_trans = 0;
    ArvoreExt aux;
    fread(&aux, sizeof(ArvoreExt), 1, arq);
    conta.num_trans++;

    conta.num_comp++;
    if(aux.indice.chave == chave){
        *index = aux.indice;
        return conta;
    }
    
    conta.num_comp++;
    if(aux.indice.chave > chave && aux.F_esq != -1){
        fseek(arq, aux.F_esq*sizeof(ArvoreExt), SEEK_SET);
        
        Comp temp = SearchArvoreExterna(arq, chave, index);
        conta.num_trans += temp.num_trans;
        conta.num_comp += temp.num_comp;
        conta.valido = temp.valido;

        return conta;
    }
    else if(aux.indice.chave < chave && aux.F_dir != -1){
        fseek(arq, aux.F_dir*sizeof(ArvoreExt), SEEK_SET);
        
        Comp temp = SearchArvoreExterna(arq, chave, index);
        conta.num_trans += temp.num_trans;
        conta.num_comp += temp.num_comp;
        conta.valido = temp.valido;

        return conta;
    }

    //Se não encontrar eu invalido e o main vai dizer que não possível encontrar
    conta.valido = 1;
    return conta;
}

//Variáveis de impressão auxiliares 
void ImprimeArvore(FILE *arq, int n){
    ArvoreExt aux;
    fseek(arq, 0, SEEK_SET);

    for(int i = 0; i < n; i++){
        fread(&aux, sizeof(ArvoreExt), 1, arq);
        printf("%d, %d, %d\n", aux.indice.chave, aux.F_esq, aux.F_dir);
    }
}

void ImprimeRegistro(Reg registro){
    printf("%d %ld %s %s\n", registro.chave , registro.dado1, registro.dado2, registro.dado3);
}