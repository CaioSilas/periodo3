#ifndef ORD_EXT_H
#define ORD_EXT_H

//Funções da Intercalação por Seleção
void intercalacaoSelecao(FILE* ArqExterno, int qnt, Comp* resultado);

void intercalacaoES(Fitas* fitas, int qnt, Comp* resultado);

void intercalacaoSE(Fitas* fitas, int qnt, Comp* resultado);

int temBloco(Fitas* fitas, int* blocosLidos, int begin, int end);

int temElemento(int* acabou);

void blocoSelecao(FILE* ArqExterno, Fitas* fitas, int qnt, Comp* resultado);

int todasCheias(Area area);

int eFim(Fitas fitas, int t);

ItemArea retiraArea(Area* area);

void insereArea(Area* area, ItemArea item);

void criaFitas(Fitas* fitas, int t);

void liberaFitas(Fitas* fitas, int t);

//Funções para auxiliar o Heap
void Troca(ItemArea *ordena, int i, int j);

int Compara(ItemArea valor1, ItemArea valor2);


//Funções necessárias para realizar o HeapSort
void Heap_Remake(ItemArea *vetor, int esq, int dir);

void Heap_RemakeEnd(ItemArea *vetor, int esq, int dir);


//Função que imprime um Registro
void ImprimeRegistro(Reg registro);

#endif//ORD_EXT_H

