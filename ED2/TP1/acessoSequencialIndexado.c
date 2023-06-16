#include "acessoSequencialIndexado.h"

void pesquisa(Indice* tabela, int tamanhoTabela, Reg* item, FILE* arquivo, Comp* resultado) {
  Reg pagina[ITENSPAGINA];
  int i, quantidadeItens;
  long desloc;
  resultado[1].num_trans = 0, resultado[1].num_comp = 0;
  resultado[1].valido = 1;

  //Procuro a página que pode ter o elemento procurado
  i = 0;
  while(i < tamanhoTabela && tabela[i].chave <= item->chave) i++;
  resultado[1].num_comp += i;

  //Função que pega o número de elementos na última página
  if(i == 0) return;
  if(i < tamanhoTabela) quantidadeItens = ITENSPAGINA;
  else {
    fseek(arquivo, 0, SEEK_END);
    quantidadeItens = ((ftell(arquivo) / sizeof(Reg)) -1) % ITENSPAGINA;
    if(quantidadeItens == 0) quantidadeItens = 4;
  }

  //fseek para voltar para a página que o elemento pode se encontrar
  desloc = (i - 1) * ITENSPAGINA * sizeof(Reg);
  fseek(arquivo, desloc, SEEK_SET);
  fread(&pagina, sizeof(Reg), quantidadeItens, arquivo);
  resultado[1].num_trans++;

  //Procuro o elemento na página e retorno se encontrar atualizando o válido
  for(i = 0; i < quantidadeItens; i++) {
    resultado[1].num_comp++;
    if(pagina[i].chave == item->chave) {
      *item = pagina[i];
      resultado[1].valido = 0;
      break;
    }
  }
  
  //Se não ocorrer a validação ele retorna vazio e não será validado assim não encontrando
  return ;
}

int acessoSequencialIndexado(FILE* arquivo, int quantidade, Reg* item, Comp* resultado) {
  //Função para calcular tempo
  clock_t tempo = clock();
  
  //Calculo quantas páginas vou ter no programa
  double tamanhoTabela = ((double) quantidade / (double) ITENSPAGINA);
  if(tamanhoTabela > quantidade / ITENSPAGINA){
    tamanhoTabela = (int) tamanhoTabela + 1;
  }

  Indice *tabela = malloc(sizeof(Indice) * tamanhoTabela);
  Reg x;
  int posicao = 0;
  resultado[0].num_comp = 0, resultado[0].num_trans = 0;
  
  //Vou lendo o primeiro elemento de todas as páginas e vou inserindo
  while (posicao < tamanhoTabela)
  {
    //Fseek vai pulando de página em página
    fread(&x, sizeof(x), 1, arquivo);
    fseek(arquivo, (sizeof(x) * (ITENSPAGINA - 1)), SEEK_CUR);
    tabela[posicao].chave = x.chave;
    resultado[0].num_trans++;
    posicao++;
  }
  //Calculo o tempo de criação
  double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
  resultado[0].temp_exec = tempoCria;

  //Função para calcular tempo
  tempo = clock();
  fflush(stdout);


  pesquisa(tabela, tamanhoTabela, item, arquivo, resultado);

  //Calculo tempo de pesquisa
  double tempoPesq = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
  resultado[1].temp_exec = tempoPesq;   

  free(tabela);

  return 1;
}