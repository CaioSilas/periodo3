#include "arvoreB.h"
#include "dados.h"

void Inicializa(TipoApontador Arvore){ //Inicializando a árvore
    Arvore = NULL;
}

int Pesquisa(Reg* x, TipoApontador Apontador, Comp *contagem, FILE *arquivo){ //Função de pesquisa da arvore
    int i = 1;

    if(Apontador == NULL){
        return 1;
    } //Chegou em uma folha e não achou o elemento

    while(i < Apontador->n && x->chave > Apontador->itens[i-1].chave) {i++; /*contagem->num_compP++;*/contagem[1].num_comp++;}

    // contagem->num_compP++;
    contagem[1].num_comp++;
    if(x->chave == Apontador->itens[i-1].chave){ //Achou o item
        // contagem->num_transP++;
        contagem[1].num_trans++;
        fseek(arquivo, Apontador->itens[i-1].posicaoArquivo * sizeof(Reg), SEEK_SET); 
        fread(x, sizeof(Reg), 1, arquivo); //Pego a posição no arquivo do item achado, e ai sim dou fread no arquivo desse item para a varaivel x
        return 0;
    }
    // contagem->num_compP++;
    contagem[1].num_comp++;
    if(x->chave < Apontador->itens[i-1].chave) //Chamando para os lados, se a chave for maior ou menor
        Pesquisa(x,Apontador->descendentes[i-1], contagem, arquivo);
    else
        Pesquisa(x, Apontador->descendentes[i], contagem, arquivo);
    return 0;
}

void InsereNaPagina(TipoApontador ApAtual, IndiceB Reg, TipoApontador ApDir, Comp *contagem){
    int NaoAchouPosicao;
    int k;
    k = ApAtual->n; NaoAchouPosicao = (k > 0);

    while(NaoAchouPosicao){ //Verificando se tem espaço na pagina para inserir
        // contagem->num_compC++;
        contagem[0].num_comp++;
        if(Reg.chave >=  ApAtual->itens[k-1].chave){
            NaoAchouPosicao = 0;
            break;
        }
        ApAtual->itens[k] = ApAtual->itens[k-1]; //Arredando os itens e ponteiros
        ApAtual->descendentes[k+1] = ApAtual->descendentes[k];
        k--;
        if(k < 1) NaoAchouPosicao = 0;
    }
    ApAtual->itens[k] = Reg;
    ApAtual->descendentes[k+1] = ApDir;
    ApAtual->n++;
}

void Ins(IndiceB Registro, TipoApontador Ap, int *Cresceu, IndiceB *RegRecursao, TipoApontador *ApRecursao, Comp *contagem){//Função que controla as inserções
    int i = 1, j;
    TipoApontador ApontadorAux;

    if(Ap == NULL){ //Atualizando o cresceu, que indica se é preciso fazer uma divisão naquele nivel, aumentando a altura
        *Cresceu = 1;
        (*RegRecursao) = Registro;
        (*ApRecursao) = NULL;
        return;
    }

    while(i < Ap->n && Registro.chave > Ap->itens[i-1].chave){ i++; contagem[0].num_comp++;} //Verificando os itens que estao numa pagina

    contagem[0].num_comp++;
    if(Registro.chave == Ap->itens[i-1].chave){ //Tentando inserir um item repetido
        *Cresceu = 0;
        return;
    }

    contagem[0].num_comp++;

    //Chama recursivamente Ins até encontrar um nó folha
    if(Registro.chave < Ap->itens[i-1].chave){ i--;  contagem[0].num_comp++;}
    Ins(Registro, Ap->descendentes[i], Cresceu, RegRecursao, ApRecursao, contagem);
    if(!*Cresceu) return;

    if(Ap->n < 2*M){ //Pagina tem espaço
        InsereNaPagina(Ap, *RegRecursao, *ApRecursao, contagem);
        *Cresceu = 0;
        return;
    }

    //Overflow: Pagina tem que ser dividida
    ApontadorAux = (TipoApontador) malloc(sizeof(TipoPagina));
    ApontadorAux->n = 0;
    ApontadorAux->descendentes[0] = NULL;

    if(i < M+1){
        InsereNaPagina(ApontadorAux, Ap->itens[2*M - 1], Ap->descendentes[2*M], contagem);
        Ap->n--;
        InsereNaPagina(Ap, *RegRecursao, *ApRecursao, contagem);
    }
    else
        InsereNaPagina(ApontadorAux, *RegRecursao, *ApRecursao, contagem);
    
    for(j = M+2; j <= 2*M; j++)
        InsereNaPagina(ApontadorAux, Ap->itens[j-1], Ap->descendentes[j], contagem);
    
    //Salva os valores para serem tratados recursivamente
    Ap->n = M; ApontadorAux->descendentes[0] = Ap->descendentes[M+1];
    *RegRecursao = Ap->itens[M]; *ApRecursao = ApontadorAux;
}

void Insere(IndiceB Registro, TipoApontador *Ap, Comp *contagem){ //Funçao que começa o processo de inserção
    int Cresceu;
    IndiceB RegRetorno;
    TipoPagina *ApRetorno, *ApAux;

    Ins(Registro, *Ap, &Cresceu, &RegRetorno, &ApRetorno, contagem);
    if(Cresceu) //Arvore crescendo um nivel
    {
        ApAux = (TipoPagina*) malloc(sizeof(TipoPagina));
        ApAux->n = 1;
        ApAux->itens[0] = RegRetorno;
        ApAux->descendentes[1] = ApRetorno;
        ApAux->descendentes[0] = *Ap;
        *Ap = ApAux;
    }
}

void ArvoreB(FILE *arquivo, int qtd, Reg* registro, Comp *contagem){ //Funçao chamada no main para começar o processo com a arvore B
    clock_t tempo = clock();
    TipoApontador Arvore;
    //Inicializando a variavel que ira contar as comparações e transferencias, que sera passada por referencia a todas minhas funções
    contagem[0].num_comp = 0;
    contagem[1].num_comp = 0;
    contagem[0].num_trans = 0;
    contagem[1].num_trans = 0;
    contagem[0].valido = 0;
    contagem[1].valido = 0;


    Reg registroLido;
    IndiceB indice;
    for(int i = 0; i < qtd; i++){ //Lendo cada um dos arquivos do arquivo, e ja inserindo ele na arvore
        fread(&registroLido, sizeof(Reg), 1, arquivo);
        contagem[0].num_trans++;
        indice.chave = registroLido.chave;
        indice.posicaoArquivo = i;
        Insere(indice, &Arvore, contagem);
    }
    double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    contagem[0].temp_exec = tempoCria;
    //Chamando a pesquisa, e recebendo seu registro, alem da contagem (que tem se a pesquisa foi sucedida e os valores finais de contagens)
    tempo = clock(); 
    Pesquisa(registro, Arvore, contagem, arquivo);
    contagem[1].valido = contagem[1].num_trans;
    
    double tempoPesq = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    contagem[1].temp_exec = tempoPesq; 
}

void ImprimeReg(Reg registro){
    printf("Chave: %d - Dados %ld | %s | %s", registro.chave, registro.dado1, registro.dado2, registro.dado3);
}
