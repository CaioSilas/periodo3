#ifndef DADOS_H
#define DADOS_H

//Definindo valor máximo de ORDENAÇÃO
#define MAXIMO 471705

//Definindo valor de FITAS
#define f 20

//Struct dos registros com os campos requisitados no enunciado do TP
typedef struct {
    long int numInscr;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];

} Reg;

//Struct necessária para contar os campos pedidos na 2° parte do enunciado
typedef struct {
    int num_transE;
    int num_transL;
    int num_comp;
    double temp_exec;
    int valido;

} Comp;

//Struct que salva a chave e a posição na memória para auxiliar na ORDENAÇÃO
typedef struct{
    FILE* fitas[2*f];
    int tamFita[2*f];
} Fitas;

//Struct que simplifica as operações com fitas
typedef struct{
    Reg reg;
    int flag;
    int fita;
} ItemArea;

//Struct que simplifica as operações na área
typedef struct{
    ItemArea iArea[20];
    int tam;
    double ultimo;
} Area;



#endif//DADOS_H

