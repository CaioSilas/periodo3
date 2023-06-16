#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "quick.h"
#include <limits.h>
#include <time.h>



int ObeterNumCelOcupadas(TipoArea *Area){
    return Area->quant; //obetendo o numero de intens que esta na area
}

void RetiraPrimeiro(TipoArea *Area,Reg *R){
    *R = Area->vector[0]; //retirando o primeiro
    for (int i = 1; i < Area-> quant;i++) //reorganizando o vector pois o primeiro foi retirado
    {
        Area->vector[i - 1] = Area->vector[i];
    }

    Area->quant--;//diminuindo a quantidades de intens que esta inseridos
}

void RetiraUltimo(TipoArea *Area,Reg *R){
    *R = Area->vector[Area->quant - 1];//tirando o ultimo
    Area->quant--;//diminuindo a quantidades de intens que esta inseridos
}

void selectionsort(TipoArea *Area,Comp *resultado){
    int menor = 0;
    for(int i = 0; i < Area->quant;i++){
        menor = i;
        for (int j = i + 1; j < Area->quant;j++){
            resultado[1].num_comp++;
            if(Area->vector[menor].nota > Area->vector[j].nota)// procurando a menor nota
            {
                menor = j;
            }
        }
        if (menor != i) //se o numero seguinte e menor que o enterio e necessario uma troca
        {
            Reg aux;
            aux = Area->vector[menor];
            Area->vector[menor] = Area->vector[i];
            Area->vector[i] = aux;
        }
    }
}

void IsereItem(Reg *UltLido,TipoArea *Area){
    Area->vector[Area->quant] = *UltLido; //colocando um intem no ultimo lugar do vector
    Area->quant++; //aumentando a quantidade de intens presentes na area
}

void FAVazia(TipoArea *Area){
    Area->quant = 0; //iniciando a quantidade de intens com 0
}

void quickSorteExterno (FILE **ArqLi, FILE **ArqEI, FILE **ArqLEs, int Esq, int Dir,Comp *resultado){
    int i;
    int j;
    TipoArea Area; //area de amarzenamento interno

    //if de condição de parada caso os ponteiros de direita e esquerda troquem de lado
    if (Dir - Esq < 1) {
        return;
    }

    FAVazia(&Area); //criando uma area vazia
    Particao(ArqLi,ArqEI,ArqLEs,Area,Esq,Dir,&i,&j,resultado); //função que inicia a partição do quick sort 

    fflush(*ArqLi);
    fflush(*ArqEI);
    fflush(*ArqLEs);

    if (i - Esq < Dir - j){
        //ordena o subarquivo menor 
        quickSorteExterno(ArqLi,ArqEI,ArqLEs,Esq,i,resultado);
        quickSorteExterno(ArqLi,ArqEI,ArqLEs,j,Dir,resultado);
    }
    else {
        quickSorteExterno(ArqLi,ArqEI,ArqLEs,j,Dir,resultado);
        quickSorteExterno(ArqLi,ArqEI,ArqLEs,Esq,i,resultado);
    }
}

void LeSup(FILE **ArqLEs,Reg *UltLido, int *Ls,bool *OndeLer,Comp *resultado){
    fseek(*ArqLEs, (*Ls - 1) * sizeof (Reg),SEEK_SET);
    fread(UltLido, sizeof(Reg),1,*ArqLEs);
    resultado[1].num_transL++;
    (*Ls)--;
    *OndeLer = false;
}

void Leinf(FILE **ArqLi, Reg *UltLido, int *Li,bool *OndeLer,Comp *resultado){
    fread(UltLido,sizeof(Reg),1,*ArqLi);
    resultado[1].num_transL++;
    // printf("leinf nota %lf \n",UltLido->nota);
    (*Li)++;
    *OndeLer = true;

}

void InserirArea(TipoArea *Area, Reg *UltLido, int *NRArea,Comp *resultado){
    //insere o ultimo lido de forma ordenada na area
    IsereItem(UltLido,Area);
    *NRArea = ObeterNumCelOcupadas(Area);
    selectionsort(Area,resultado);//metodo que ordena a area
}

void EscreveMax(FILE **ArqLEs, Reg R,int *Es,Comp *resultado){
    fseek(*ArqLEs,(*Es-1) * sizeof(Reg),SEEK_SET);
    fwrite(&R,sizeof(Reg),1,*ArqLEs);
    resultado[1].num_transE++;
    // while(fread(&R,sizeof(Reg),1, *ArqLEs)){
    //     printf("%ld\t%.2lf\t%s\t%s\t%s\n",R.numInscr,R.nota,R.estado,R.cidade,R.curso);
    // }
    (*Es)--;
}

void EscreveMin(FILE **ArqEI,Reg R, int *Ei,Comp *resultado){
    fwrite(&R,sizeof(Reg),1,*ArqEI);
    resultado[1].num_transE++;
    // while(fread(&R,sizeof(Reg),1, *ArqEI)){
    //     printf("%ld\t%.2lf\t%s\t%s\t%s\n",R.numInscr,R.nota,R.estado,R.cidade,R.curso);
    // }
    (*Ei)++;

}

void RetiraMax(TipoArea *Area,Reg *R, int *NRArea){
    // selectionsort(Area);
    RetiraUltimo(Area,R);
    *NRArea = ObeterNumCelOcupadas(Area);

}

void RetiraMin(TipoArea *Area,Reg *R,int *NRArea){
    // selectionsort(Area);
    RetiraPrimeiro(Area,R);
    *NRArea = ObeterNumCelOcupadas(Area);
}

void Particao (FILE **ArqLi,FILE **ArqEI,FILE **ArqLEs,TipoArea Area,int Esq, int Dir,int *i,int *j,Comp *resultado){
    int Ls = Dir,Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    double Linf = INT_MIN, Lsup = INT_MAX;
    bool OndeLer = true;
    Reg UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(Reg),SEEK_SET);
    fseek(*ArqEI, (Ei - 1) * sizeof(Reg),SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;

    while(Ls >= Li)//lendo a parte superio e inferio e colancando elas na area
    {
        if (Area.quant < TAMAREA - 1) 
        {
            if (OndeLer){
                LeSup(ArqLEs,&UltLido,&Ls,&OndeLer,resultado);
            }
            else {
                Leinf(ArqLi,&UltLido,&Li,&OndeLer,resultado);
            }
            InserirArea(&Area,&UltLido,&NRArea,resultado); // inserindo um intem na area
            continue;
        }
    
        if (Ls == Es){
            LeSup(ArqLEs,&UltLido,&Ls,&OndeLer,resultado);
        }
        else if (Li == Ei){
            Leinf(ArqLi,&UltLido,&Li,&OndeLer,resultado);
        }
        else if (OndeLer){
            LeSup(ArqLEs,&UltLido,&Ls,&OndeLer,resultado);
        }
        else {
            Leinf(ArqLi,&UltLido,&Li,&OndeLer,resultado);
        }

        resultado[1].num_comp++;
        if (UltLido.nota > Lsup){
            *j = Es;
            EscreveMax(ArqLEs,UltLido,&Es,resultado);
            continue;
        }
        resultado[1].num_comp++;
        if (UltLido.nota < Linf){
            *i = Ei;
            EscreveMin(ArqEI,UltLido,&Ei,resultado);
            continue;
        }
        InserirArea(&Area,&UltLido,&NRArea,resultado);

        if (Ei-Esq < Dir -Es){
            RetiraMin(&Area,&R,&NRArea);
            EscreveMin(ArqEI,R,&Ei,resultado);
            Linf = R.nota;
        }

        else{
            RetiraMax(&Area,&R,&NRArea);
            EscreveMax(ArqLEs,R,&Es,resultado);
            Lsup = R.nota;
        }
    
    }

    while(Ei <= Es){
        RetiraMin(&Area,&R,&NRArea);
        EscreveMin(ArqEI,R,&Ei,resultado);
    }
}

void inicia(char *nome,int qnt,Comp *resultado ){
	clock_t tempo = clock(); //inicio do clock usado para contrar o tempo

    resultado[1].num_comp = 0;
    resultado[1].num_transE = 0;
    resultado[1].num_transL = 0;
    resultado[1].valido = 0;

    FILE *ArgLEs; //arquivos que serao usados para leitura e escrita
    FILE *ArgLi;
    FILE *ArgEi;
    
    Reg R;

    //Abrindo os arquivos para leitura e escrita
   ArgLi = fopen(nome,"r+b");
    if(ArgLi == NULL){
        printf ("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    ArgEi = fopen(nome,"r+b");
    
    if(ArgEi == NULL){
        printf ("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    ArgLEs = fopen(nome,"r+b");
    
    if(ArgLEs == NULL){
        printf ("Arquivo nao pode ser aberto\n");
        exit(1);
    }
    
    quickSorteExterno (&ArgLi,&ArgEi,&ArgLEs,1,qnt,resultado); //função que inicia o metodo sort
    double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC; //calculo para tranformar o tempo de execusao em segundos

    resultado[1].temp_exec = tempoCria;
 
    fflush(ArgLi);
    fclose(ArgEi);
    fclose(ArgLEs);
    fseek(ArgLi,0,SEEK_SET);
    
    while(fread(&R,sizeof(Reg),1, ArgLi)){
        printf("%ld\t%.2lf\t%s\t%s\t%s\n",R.numInscr,R.nota,R.estado,R.cidade,R.curso);
    }
    
    resultado[1].valido = 1; // mundando o valor da varialvel para indicar que uma ordenação foi feita
    
    fclose(ArgLi);
    
}