#include <stdio.h>
#include <time.h>
#include "arvoreBE.h"
#include "dados.h"

void InicializaBE(TipoApontadorE Arvore){ //Inicializando a árvore
    Arvore = NULL;
}

void PesquisaBE(Reg *x, TipoApontadorE *Apontador, Comp *contagem){//Pesquisa na árvore BE recursivamente
    int i;
    TipoApontadorE PaginaAtual;
    PaginaAtual = *Apontador;
    //Se for interna ela precisa chamar recursivamente até encontrar uma página externa
    if((*Apontador)->seletor == Interna){
        i = 1;
        //Procura a posição do ponteiro
        while(i < PaginaAtual->Paginas.Inter.nInterno && x->chave > PaginaAtual->Paginas.Inter.chavesInternas[i-1]){contagem[1].num_comp++; i++; }
        
        contagem[1].num_comp++;
        if(x->chave <= PaginaAtual->Paginas.Inter.chavesInternas[i-1]){
            PesquisaBE(x, &PaginaAtual->Paginas.Inter.descendentesInternos[i-1], contagem);
        }
        else{
            PesquisaBE(x, &PaginaAtual->Paginas.Inter.descendentesInternos[i], contagem);
        }
        return;
    }
    //Já fora na externa ele vai procurar a posição e conferir se esta existe
    i = 1;
    while( i <= PaginaAtual->Paginas.Exter.nExterno && x->chave > PaginaAtual->Paginas.Exter.registrosExternos[i-1].chave){
        i++;
        contagem[1].num_comp++;
    }

    //Se encontrar é valido
    if(x->chave == PaginaAtual->Paginas.Exter.registrosExternos[i-1].chave){
        *x = PaginaAtual->Paginas.Exter.registrosExternos[i-1];
        contagem[1].valido = 1;
    }
    //Se não é invalido
    else
        contagem[1].valido = 0;
}

void InsereNaPaginaInt(TipoApontadorE ApAtual, int Reg, TipoApontadorE ApDir, Comp *contagem){
    int NaoAchouPosicao;
    int k;
    k = ApAtual->Paginas.Inter.nInterno; NaoAchouPosicao = (k > 0);

    while(NaoAchouPosicao){ //Verificando se tem espaço na pagina para inserir
        contagem[0].num_comp++;
        if(Reg >=  ApAtual->Paginas.Inter.chavesInternas[k-1]){
            NaoAchouPosicao = 0;
            break;
        }
        ApAtual->Paginas.Inter.chavesInternas[k] = ApAtual->Paginas.Inter.chavesInternas[k-1]; //Arredando os itens e ponteiros
        ApAtual->Paginas.Inter.descendentesInternos[k+1] = ApAtual->Paginas.Inter.descendentesInternos[k];
        k--;
        if(k < 1) NaoAchouPosicao = 0;
    }
    //Alterando os valores
    ApAtual->Paginas.Inter.chavesInternas[k] = Reg;
    ApAtual->Paginas.Inter.descendentesInternos[k+1] = ApDir;
    ApAtual->Paginas.Inter.nInterno++;
}

void InsereNaPaginaExt(TipoApontadorE ApAtual, Reg Reg, Comp *contagem){
    int NaoAchouPosicao;
    int k;
    k = ApAtual->Paginas.Exter.nExterno; 
    NaoAchouPosicao = (k > 0);
    
    while(NaoAchouPosicao){ //Verificando se tem espaço na pagina para inserir
        contagem[0].num_comp++;
        if(Reg.chave >=  ApAtual->Paginas.Exter.registrosExternos[k-1].chave){
            NaoAchouPosicao = 0;
            break;
        }
        ApAtual->Paginas.Exter.registrosExternos[k] = ApAtual->Paginas.Exter.registrosExternos[k-1]; //Arredando os itens e ponteiros
        k--;
        if(k < 1) NaoAchouPosicao = 0;
    }
    //Alterando os valores
    ApAtual->Paginas.Exter.registrosExternos[k] = Reg;
    ApAtual->Paginas.Exter.nExterno++;
}

void InsBE(Reg Registro, TipoApontadorE Ap, int *Cresceu, Reg *RegRecursao, TipoApontadorE *ApRecursao, Comp *contagem){//Função que controla as inserções
    int i = 1, j;
    TipoApontadorE ApontadorAux;

    if(Ap == NULL){ //Atualizando o cresceu, que indica se é preciso fazer uma divisão naquele nivel, aumentando a altura
        *Cresceu = 1;
        (*RegRecursao) = Registro;
        (*ApRecursao) = NULL;
        return;
    }

    //Se for interna você tem que chamar recursivamente até ser externa
    if(Ap->seletor == Interna){
        while(i < Ap->Paginas.Inter.nInterno && Registro.chave > Ap->Paginas.Inter.chavesInternas[i-1]){ i++; contagem[0].num_comp++;} //Verificando os itens que estao numa pagina


        contagem[0].num_comp++;
        if(Registro.chave < Ap->Paginas.Inter.chavesInternas[i-1]){ i--; contagem[0].num_comp++;}
        InsBE(Registro, Ap->Paginas.Inter.descendentesInternos[i], Cresceu, RegRecursao, ApRecursao, contagem);
        if(!*Cresceu) return;


        //Se voltar na página interna e ter que inserir temos que verificar se é possível ou se tem que haver uma manutenção

        if(Ap->Paginas.Inter.nInterno < 2*M){ //Pagina tem espaço
            InsereNaPaginaInt(Ap, RegRecursao->chave, *ApRecursao, contagem);
            *Cresceu = 0;
            return;
        }

        //Overflow: Pagina tem que ser dividida
        
        //Mesma função da árvore B
        ApontadorAux = (TipoApontadorE) malloc(sizeof(TipoPaginaE));
        ApontadorAux->seletor = Interna;
        ApontadorAux->Paginas.Inter.nInterno = 0;
        ApontadorAux->Paginas.Inter.descendentesInternos[0] = NULL;

        if(i < M+1){
            InsereNaPaginaInt(ApontadorAux, Ap->Paginas.Inter.chavesInternas[2*M - 1], Ap->Paginas.Inter.descendentesInternos[2*M], contagem);
            Ap->Paginas.Inter.nInterno--;
            InsereNaPaginaInt(Ap, RegRecursao->chave, *ApRecursao, contagem);
        }
        else{
            InsereNaPaginaInt(ApontadorAux, RegRecursao->chave, *ApRecursao, contagem);
        }
        
        for(j = M+2; j <= 2*M; j++)
            InsereNaPaginaInt(ApontadorAux, Ap->Paginas.Inter.chavesInternas[j-1], Ap->Paginas.Inter.descendentesInternos[j], contagem);
        
        Ap->Paginas.Inter.nInterno = M; ApontadorAux->Paginas.Inter.descendentesInternos[0] = Ap->Paginas.Inter.descendentesInternos[M+1];
        RegRecursao->chave = Ap->Paginas.Inter.chavesInternas[M]; *ApRecursao = ApontadorAux;
    }
    else{ //continuar... Quando é pagina externa
        //Atualiza o Reg de recursão
        (*RegRecursao) = Registro;

        //Procura posição
        while(i < Ap->Paginas.Exter.nExterno && Registro.chave > Ap->Paginas.Exter.registrosExternos[i-1].chave){ i++; contagem[0].num_comp++;} //Verificando os itens que estao numa pagina

        contagem[0].num_comp++;
        if(Registro.chave == Ap->Paginas.Exter.registrosExternos[i-1].chave && Ap->Paginas.Exter.nExterno != 0){ //Tentando inserir um item repetido
            *Cresceu = 0;
            return;
        }

        contagem[0].num_comp++;
        if(!*Cresceu) return;

        if(Ap->Paginas.Exter.nExterno < 2*M){ //Pagina tem espaço
            InsereNaPaginaExt(Ap, *RegRecursao, contagem);
            *Cresceu = 0;
            return;
        }

        //Overflow: Pagina tem que ser dividida
        ApontadorAux = (TipoApontadorE) malloc(sizeof(TipoPaginaE));
        ApontadorAux->seletor = Externa;
        ApontadorAux->Paginas.Exter.nExterno = 0;
        
        //Se o registro for menor ficará na página que já existe
        //Se não irá ir para a nova página criada

        if(i < M+1){
            InsereNaPaginaExt(ApontadorAux, Ap->Paginas.Exter.registrosExternos[2*M - 1], contagem);
            Ap->Paginas.Exter.nExterno--;
            InsereNaPaginaExt(Ap, *RegRecursao, contagem);
        }
        else{
            InsereNaPaginaExt(ApontadorAux, *RegRecursao, contagem);
        }
        for(j = M+2; j <= 2*M; j++)
            InsereNaPaginaExt(ApontadorAux, Ap->Paginas.Exter.registrosExternos[j-1], contagem);
        
        //Atualizando os valores recursivos
        Ap->Paginas.Exter.nExterno = M + 1;
        *RegRecursao = Ap->Paginas.Exter.registrosExternos[M]; *ApRecursao = ApontadorAux;
    }
    
}

void InsereBE(Reg Registro, TipoApontadorE *Ap, Comp *contagem){ //Funçao que começa o processo de inserção
    
    
    int Cresceu;
    Cresceu = 1;
    Reg RegRetorno;
    TipoPaginaE *ApRetorno, *ApAux;

    //Criando a primeira página externa se for necessário
    if(*Ap == NULL){
        ApAux = (TipoPaginaE*) malloc(sizeof(TipoPaginaE));
        ApAux->seletor = Externa;
        ApAux->Paginas.Exter.nExterno = 0;
        *Ap = ApAux;
    }

    InsBE(Registro, *Ap, &Cresceu, &RegRetorno, &ApRetorno, contagem);

    if(Cresceu) //Arvore crescendo um nivel
    {
        ApAux = (TipoPaginaE*) malloc(sizeof(TipoPaginaE));
        ApAux->seletor = Interna;
        ApAux->Paginas.Inter.nInterno = 1;
        ApAux->Paginas.Inter.chavesInternas[0] = RegRetorno.chave;
        ApAux->Paginas.Inter.descendentesInternos[1] = ApRetorno;
        ApAux->Paginas.Inter.descendentesInternos[0] = *Ap;
        *Ap = ApAux;
    }
}

void ArvoreBE(FILE *arquivo, int qtd, Reg* registro, Comp* contagem){ //Funçao chamada no main para começar o processo com a arvore B
    TipoApontadorE Arvore;
    //Inicializando a variavel que ira contar as comparações e transferencias, que sera passada por referencia a todas minhas funções
    contagem[0].num_comp = 0;
    contagem[1].num_comp = 0;
    contagem[0].num_trans = 0;
    contagem[1].num_trans = 0;
    contagem[1].valido = 0;

    clock_t tempo = clock();

    Reg registroLido;
    for(int i = 0; i < qtd; i++){ //Lendo cada um dos arquivos do arquivo, e ja inserindo ele na arvore
        fread(&registroLido, sizeof(Reg), 1, arquivo);
        contagem[0].num_trans++;
        InsereBE(registroLido, &Arvore, contagem);
    }
    double tempoCria = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    contagem[0].temp_exec = tempoCria;

    tempo = clock();

    PesquisaBE(registro, &Arvore, contagem);

    double tempoPesq = ((double)(clock() - tempo))/CLOCKS_PER_SEC;
    contagem[1].temp_exec = tempoPesq;

    //Chamando a pesquisa, e recebendo seu registro, alem da contagem (que tem se a pesquisa foi sucedida e os valores finais de contagens)
}

//Função externa auxiliar que imprime a árvore B* 

void imprimeExterna(TipoApontadorE arv){
    while (arv->Paginas.Exter.registrosExternos->chave != 80)
    {
        if(arv->seletor != Externa){
            printf("Interno:\n");

            for(int i = 0; i < arv->Paginas.Exter.nExterno; i++){
                printf("%d ", arv->Paginas.Inter.chavesInternas[i]);
            }
            printf("--\n");

            for(int i = 0; i < arv->Paginas.Inter.nInterno+1; i++){ 
                imprimeExterna(arv->Paginas.Inter.descendentesInternos[i]);
                
            }
            return;
        }
        else{
            printf("Externo:\n");

            for(int i = 0; i < arv->Paginas.Exter.nExterno; i++){
                printf("%d ", arv->Paginas.Exter.registrosExternos[i].chave);
            }
            printf("\n");
            return;
        }
        /* code */
    }
    
}