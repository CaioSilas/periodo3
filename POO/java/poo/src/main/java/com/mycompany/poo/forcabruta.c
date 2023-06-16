#define MAXTAMTEXTO 1000
#define MAXTAMPADRAO 10
#define MAXCHAR 256
#define NUMMAXEROS 10
#include <stdio.h>

typedef char TipoTexto [MAXTAMTEXTO];
typedef char TipoPadrao [MAXTAMPADRAO];




//m = o tamanho do padrao
void forcaBruta(TipoTexto T, long int n, TipoPadrao P, long int m){
    long int i , j , k;

    for (i = 1; i <= (n- m -1); i++){
        j = 1;
        k = i;

        while (T[k-1] == P[j - 1] && j <= m)
        {
            j++;
            k++;
        }
        
        if (j > m ){
            printf ("Casamento exato %ld\n",i);
        }

    }
}

// void bmh (TipoTexto T, long int n, TipoPadrao P, long int m){

//     long int i,j,k,d[MAXCHAR + 1];

//     for (j = 0; j <= MAXCHAR; j++){
//         d[j] = m;//BMHS = m + 1
//     }

//     for (j = 1; j <m;j++){ //BMHS j <= m
//         d[P[j - 1]] = m - j; //BMHS m - j + 1 
//     }

//     i = m;

//     while (i <= n)
//     {
//         k = i;
//         j = m;

//         while (T[k - 1] == P[j - 1] && j > 0){k--;j--;}
        
//         if (j == 0){
//             printf ("Casamento na posicao %ld\n",k + 1);
            
//         }
//         i += d[T[i - 1]]; // BMHS d[T[i]]
//     }
// }


void bmh(TipoTexto T, long int n, TipoPadrao P, long int m){
   long int i,j,k,d[MAXCHAR + 1];

    for (j = 0; j <= MAXCHAR;j++){
        d[j] = m;
    }
    for (j = 1; j < m;j++){
        d[P[j - 1]] = m - j;
    }

    i = m;
    while(i < n){
        j = i; k=m;
        while (T[k - 1] == P[j - 1] && j > 0)
        {
            k--;j--;
        }
        if (j == 0){
            printf("%ld", k+ 1);
        }
        i+=d[T[i - 1]];


    }





}




void bmhs (TipoTexto T,long int n, TipoPadrao P,long int m){
    long int i,j,k,d[MAXCHAR + 1];

    for (j = 0; j <= MAXTAMPADRAO; j++){
        d[j] = m + 1;
    }

    for (j = 1; j <= m; j++){
        d[P[j - 1]] = m - j + 1;
    }

    i = m;

    while (i <= n)
    {
        k = i;
        j = m;

        while (T[k - 1] == P[j - 1] && j > 0)
        {
            k--;j--;
        }
        if (j == 0){
            printf("casamento na cadeia %ld", k + 1);
        }
        i += d[T[i]];


    }
    




}









int main(){
    TipoTexto T = "os testes testem";
    TipoPadrao P = "teste";
    /*
    T = 1 
    E = 3
    S = 2
    */

    long int m = 5;

    long int n = 15;

    // forcaBruta(T,n,P,m);
    bmh(T,n,P,m);


    return 0;
}