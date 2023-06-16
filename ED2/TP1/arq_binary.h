//Autores: Henrique Dantas Pighini 21.1.4025

#ifndef ARQ_BINARY_H
#define ARQ_BINARY_H

//Struct que representa uma árvore binária em um arquivo
typedef struct{
    //Índice que salva a chave e a posição de memória
    Indice indice;
    int F_esq, F_dir;

} ArvoreExt;

//Função que chama as funções que montam e que pesquisam na árvore e recebe uma variável que será sobrecarregada com os valores de complexidade de desempenho
void ArvoreExterna(FILE *arq, int qnt, Reg *registro, Comp* resultado);

//Função que procura um elemento na árvore e retorna os números de complexidade de desempenho
Comp SearchArvoreExterna(FILE *arq, int chave, Indice *index);

//Função que insere um elemento na árvore binária e retorna os números de complexidade de desempenho
Comp InsertArvoreExterna(FILE *arq, Indice index);

//Funções que imprimem
void ImprimeArvore(FILE *arq, int n);
void ImprimeRegistro(Reg registro);

#endif//ARQ_BINARY_H