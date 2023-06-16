#include "functions.h"

#include "Livro.h"
#include "Impresso.h"
#include "Eletronico.h"
#include "AudioBook.h"


//B
vector <Livro*> idiomaCatch(vector <Livro*> biblioteca, string idioma){
    //Função que retorna um vetor com todos os livros com o idioma igual ao que foi passado
    vector <Livro*> retorno;    
    for(int i = 0; i < biblioteca.size(); i++){
        if(biblioteca[i]->getIdiomaOriginal() == idioma){
            retorno.insert(retorno.end(), biblioteca[i]);
        }
    }


    return retorno;
}
//C
vector <Livro*> formatoCatch(vector <Livro*> biblioteca, string formato){
    //Função que retorna um vetor com todos os livros eletrônicos com o formato igual ao que foi passado
    
    vector <Livro*> retorno;
    Eletronico *E;
    
    for(int i = 0; i < biblioteca.size(); i++){
        //Verifico se o elemento da biblioteca é Eletronico
        if((E = dynamic_cast<Eletronico*>(biblioteca[i])) != NULL){
            if(formato == E->getFormatoArquivo()){
                retorno.insert(retorno.end(), biblioteca[i]);
            }
        }
    }

    //Função sort para ordenar o vetor retornado pelo ano de publicação
    sort(retorno.begin(), retorno.end(), [](Livro* lv1, Livro* lv2){return lv1->getAnoPublicacao() < lv2->getAnoPublicacao();});

    return retorno;
}
//D
vector <Livro*> numLivrariaCatch(vector <Livro*> biblioteca, int qnt){

    //Função que retorna um vetor com todos os livros impressos com um número maior ou igual de livrarias passado
    vector <Livro*> retorno;
    Impresso *I;
    
    for(int i = 0; i < biblioteca.size(); i++){
        //Verifico se o elemento da biblioteca é Impresso
        if((I = dynamic_cast<Impresso*>(biblioteca[i])) != NULL){
            if(qnt <= I->getLivrarias().size()){
                retorno.insert(retorno.end(), biblioteca[i]);
            }
        }
    }

    return retorno;
}
//E
bool escritorCatch(vector <Livro*> biblioteca, string escritor){
    //Função que retorna um vetor com todos os livros com o escritor igual ao que foi passado
    
    for(int i = 0; i < biblioteca.size(); i++){
        for(int j = 0; j < biblioteca[i]->getEscritores().size(); j++){
            if(escritor == biblioteca[i]->getEscritores()[j]){
                return true;
            }
        }
    }
    

    return false;
}
//F
vector <Livro*> tituloCatch(vector <Livro*> biblioteca, string titulo){
    //Função que retorna um vetor com todos os livros com o titulo igual ao que foi passado
    vector <Livro*> retorno;
    
    for(int i = 0; i < biblioteca.size(); i++){
        if(biblioteca[i]->getTitulo() == titulo){
            retorno.insert(retorno.end(), biblioteca[i]);
        }
    }

    return retorno;
}
//G
vector <string> keywordCatch(vector <Livro*> biblioteca){
    //Função que retorna um vetor com todas as keywords sem repetir
    
    vector <string> result;
    vector <string> aux;

    for(int i = 0; i < biblioteca.size(); i++){
        for(int j = 0; j < biblioteca[i]->getKeywords().size();j++){
            aux.insert(aux.end(), biblioteca[i]->getKeywords()[j]); 
        }
    }
    //Esse for vai pegar o vetor com todas as keywords criado a cima e vai passar pelo vetor inserindo somente os que não tiverem repetidos
    for(int i =  0 ; i < aux.size(); i++){
        if(find(result.begin(), result.end(), aux[i]) == result.end()){
            result.insert(result.end(), aux[i]);
        }

    }
    return result;
}
//H
vector <Livro*> numCapituloCatch(vector <Livro*> biblioteca, int qnt){
    //Função que retorna um vetor de livros com número menor de capitulos do que o passado por argumento
    vector <Livro*> retorno;

    for(int i = 0; i < biblioteca.size(); i++){
        if(qnt >= biblioteca[i]->getCapitulos().size()){
            retorno.insert(retorno.end(), biblioteca[i]);
        }
    }

    //Sort ordenando o vetor de livros em função alfabética do nome do autor
    sort(retorno.begin(), retorno.end(), [](Livro* lv1, Livro* lv2){return lv1->getEscritores()[0] < lv2->getEscritores()[0];});


    return retorno;
}
//I
vector<vector<Livro*>::iterator> returnIterators(vector <Livro*>& biblioteca, string titulo){
    //Função que retorna um vetor de iterator com o mesmo do que foi passado por argumento
    vector<vector<Livro*>::iterator> x;
    for(auto itr = biblioteca.begin(); itr != biblioteca.end(); ++itr){
        if((*itr)->getTitulo() == titulo){
            x.push_back(itr);
        }
    }
    return x;
}
//J
void allCatch(vector <Livro*> biblioteca, bool option){
    //Função que pega um vector de livros e imprime ele em um arquivo ou em um terminal
    Impresso *I;
    Eletronico *E;
    AudioBook *A;

    vector<Livro*> L;
	ofstream saida;
	if (!option) { //caso o usuario nao deseje visualizar no terminal
		saida.open("saida.txt");
		if (saida.is_open()) {
			for (auto i : biblioteca) {
				if ((I = dynamic_cast<Impresso*>(i)) != NULL) { 
					saida << *I; //escreve no arquivo
				} else if ((E = dynamic_cast<Eletronico*>(i)) != NULL) { 
					saida << *E;
				} else if ((A = dynamic_cast<AudioBook*>(i)) != NULL) { 
					saida << *A;
				}
			}
			saida.close();
			cout << "\nArquivo criado.\n";
		} else {
			cout << "\nNao foi possivel criar o arquivo para escrever a saida.\n";
		}
	} else {
        for (auto i : biblioteca) {
            if ((I = dynamic_cast<Impresso*>(i)) != NULL) { 
                cout << *I;//escreve no terminal
            } else if ((E = dynamic_cast<Eletronico*>(i)) != NULL) { 
                cout << *E;
            } else if ((A = dynamic_cast<AudioBook*>(i)) != NULL) { 
                cout << *A;
            }
        }
	}
}

//k
int keywordSearch(vector <Livro*> biblioteca, string keyword){
    //Retorna um número de keywords encontradas iguais à keyword passada por parâmetro
    vector <Livro*> retorno;

    for(int i = 0; i < biblioteca.size(); i++){
        for(int j = 0; j < biblioteca[i]->getKeywords().size(); j++){
            if(keyword == biblioteca[i]->getKeywords()[j]){
                retorno.insert(retorno.end(), biblioteca[i]);
            }
        }
    }
    return retorno.size();
}
//L
Mmid mapea(vector<Livro*> biblioteca){
    //Função que faz um map dos livros

    //Indices serão organizados pelos index abaixo
    string English = "ING";
    string Espano = "ESP";
    string Francais = "FRS";
    string Portuguese = "POT";

    Mmid mapeamento;

    //Realiza o mapeamento
    for(int i = 0; i < biblioteca.size(); i++){
        if(biblioteca[i]->getIdiomaOriginal() == "Ingles"){
            mapeamento.insert(Mmid::value_type(English, biblioteca[i]));
        }
        if(biblioteca[i]->getIdiomaOriginal() == "Espanhol"){
            mapeamento.insert(Mmid::value_type(Espano, biblioteca[i]));
        }
        if(biblioteca[i]->getIdiomaOriginal() == "Frances"){
            mapeamento.insert(Mmid::value_type(Francais, biblioteca[i]));
        }
        if(biblioteca[i]->getIdiomaOriginal() == "Portugues"){
            mapeamento.insert(Mmid::value_type(Portuguese, biblioteca[i]));
        }
    }

    return mapeamento;

}