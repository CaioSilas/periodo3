#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define milhao 1000000

typedef struct {
    int chave;
    long int dado1;
    char dado2[1000];
    char dado3[5000];

} Dados;

// int main(){

//     int *v = calloc(milhao, sizeof(int));
//     FILE *arq = fopen("registros_aleatorio.bin", "wb");
//     if(arq == NULL){
//         return 0;
//     }

//     Dados dado;

//     srand(time(NULL));

//     int valido = 0;
//     for(int i = 0; i < milhao; i++){
//         valido = 0;
//         while(valido == 0){
//             dado.chave = (rand() % milhao);
//             if(v[dado.chave] == 0){
//                 v[dado.chave] = 1;
//                 valido = 1;
//             }
//         }
//         dado.dado1 = i*2;
//         for(int j = 0; j < 999; j++){
//             dado.dado2[j] = (rand() % 26) + 65;
//         }
//         dado.dado2[999]= '\0'; 
        
//         for(int j = 0; j < 4999; j++){
//             dado.dado3[j] = (rand() % 26) + 65;
//         }
//         dado.dado3[4999]= '\0'; 

        
//         fwrite(&dado, sizeof(Dados), 1, arq);
//     }
//     fclose(arq);
//     return 0;
// }

// int main(){

//     FILE *arq = fopen("registros_cres.bin", "wb");
//     if(arq == NULL){
//         return 0;
//     }

//     Dados dado;

//     srand(time(NULL));

//     for(int i = 0; i < milhao; i++){
//         dado.chave = i;
//         dado.dado1 = i*2;
//         for(int j = 0; j < 999; j++){
//             dado.dado2[j] = (rand() % 26) + 65;
//         }
//         dado.dado2[999]= '\0'; 
        
//         for(int j = 0; j < 4999; j++){
//             dado.dado3[j] = (rand() % 26) + 65;
//         }
//         dado.dado3[4999]= '\0'; 

//         fwrite(&dado, sizeof(Dados), 1, arq);
//     }
//     fclose(arq);
//     return 0;
// }

// int main(){

//     FILE *arq = fopen("registros_decres.bin", "wb");
//     if(arq == NULL){
//         return 0;
//     }

//     Dados dado;

//     srand(time(NULL));

//     for(int i = milhao -1; i <= 0; i--){
//         dado.chave = i;
//         dado.dado1 = i*2;
//         for(int j = 0; j < 999; j++){
//             dado.dado2[j] = (rand() % 26) + 65;
//         }
//         dado.dado2[999]= '\0'; 
        
//         for(int j = 0; j < 4999; j++){
//             dado.dado3[j] = (rand() % 26) + 65;
//         }
//         dado.dado3[4999]= '\0'; 

//         fwrite(&dado, sizeof(Dados), 1, arq);
//     }
//     fclose(arq);
//     return 0;
// }