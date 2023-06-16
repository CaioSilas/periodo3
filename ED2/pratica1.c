//Caio silas - Matricula : 21.1.4111
//Turmas 21-22


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    int matricula;
    char nome[25];
    double nota1;
    double nota2;
    double nota3;
    int faltas;
    char conceito;
    double media;
}TAluno;

void salva(TAluno *aluno){

    FILE *arquivo2 = fopen("conceito.txt","w+");
    
    for (int i = 0;i < 5;i++){
        fprintf(arquivo2,"%d ",aluno[i].matricula);
        fputs(aluno[i].nome,arquivo2);
        fputc(aluno[i].conceito,arquivo2);
        fputs("\n",arquivo2);

    }

    fclose(arquivo2);
}

void salva2(TAluno *aluno){

    FILE *arquivo2 = fopen("conceito2.txt","w+");
    
    for (int i = 0;i < 5;i++){
        fprintf(arquivo2,"%d ",aluno[i].matricula);
        fputs(aluno[i].nome,arquivo2);
        fputc(aluno[i].conceito,arquivo2);
        fputs("\n",arquivo2);

    }

    fclose(arquivo2);
}

void salvabinario(TAluno *aluno){
    FILE *arquivo2 = fopen("alunos.bin","w+b");

    for (int i = 0; i < 5; i++)
    {
        fwrite(&aluno[i], sizeof(TAluno), 1, arquivo2);
    }
    
    fclose(arquivo2);

}

int main(){
    FILE *arquivo = fopen("alunos.txt","r");

    TAluno *aluno;
    aluno = calloc(5,sizeof(TAluno));

    if (arquivo != NULL){
        for (int i = 0; i < 5; i++){
            fscanf(arquivo,"%d",&aluno[i].matricula);
            fgets(aluno[i].nome,29,arquivo);
            fscanf(arquivo,"%lf",&aluno[i].nota1);
            fscanf(arquivo,"%lf",&aluno[i].nota2);
            fscanf(arquivo,"%lf",&aluno[i].nota3);
            fscanf(arquivo,"%d",&aluno[i].faltas);
            aluno[i].media = (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;

            if (aluno[i].faltas >= 18){
                aluno[i].conceito = 'F';
            }
            else if (aluno[i].faltas <= 18 && aluno[i].media < 6.0){
                aluno[i].conceito = 'R';
            }
            else if (aluno[i].faltas <= 18 && aluno[i].media >= 6.0 && aluno[i].media < 7.5){
                aluno[i].conceito = 'C';
            }
            else if (aluno[i].faltas <= 18 && aluno[i].media >= 7.5 && aluno[i].media <= 9.0){
                aluno[i].conceito = 'B';
            }
            else {
                aluno[i].conceito = 'A';
            }
        }
        
        fclose(arquivo);
    }
    else {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO");
        exit(1);
    }
    
    salva(aluno);
    salvabinario(aluno);

    FILE *arquivo1 = fopen("alunos.bin","r+b");

    TAluno *aux = calloc(5,sizeof(TAluno));

    if (arquivo1 != NULL){
        for (int i = 0; i < 5; i++){
            fread(&aux[i], sizeof(TAluno), 1, arquivo1);
        }
        
        fclose(arquivo1);
    }
    else {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO");
        exit(1);
    }

    salva2(aux);

    free(aux);
    free(aluno);
    
    return 0;
}
