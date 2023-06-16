//Autores: Henrique Dantas Pighini 21.1.4025
#ifndef DADOS_H
#define DADOS_H

//Struct dos registros com os campos requisitados no enunciado do TP
typedef struct {
    int chave;
    long int dado1;
    char dado2[1000];
    char dado3[5000];
} Reg;

//Struct necessária para contar os campos pedidos na 2° parte do enunciado
typedef struct {
    int num_trans;
    int num_comp;
    double temp_exec;
    int valido;
} Comp;

//Struct que salva a chave e a posição na memória para auxiliar na pesquisa
typedef struct{
    int chave;
    int posicaoArq;
} Indice;



#endif//DADOS_H

