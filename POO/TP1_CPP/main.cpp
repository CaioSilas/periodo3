#include "functions.h"

//TP CPP 1

//Funções utilizados estão no header functions


//Função fornecida pelo professor para dividir um string em um vetor de string a partir de um delimitador
void split(const string& str, vector<string>& cont, char delim = ';') {
    stringstream ss(str); 
    string token;
    while (getline(ss, token, delim)) 
    cont.push_back(token); 
}


int main(){

    //Vetor que armazenamos todos os livros
    vector <Livro*> biblioteca;
    
    for(int i = 1; i <= 16; i++){ 

        //Variáveis para auxiliar no insert
        int tipo;
        vector <string> escritores;
        vector <string> keywords;
        vector <string> capitulos;
        vector <string> livrarias;

        string titulo;
        string escritor;
        int ano;
        string idioma;
        string key;
        string cap;

        string arquivo;

        //Crio a varíavel para ler do arquivo
        arquivo = to_string(i) + ".txt";

        ifstream inFile(arquivo);

        inFile >> tipo;
        
        //Realizo a leitura

        getline(inFile, titulo);
        getline(inFile, titulo);

        getline(inFile, escritor);

        split(escritor, escritores);

        inFile >> ano;

        getline(inFile, idioma);
        getline(inFile, idioma);


        getline(inFile, key);
        split(key, keywords);

        getline(inFile, cap);
        split(cap, capitulos);


        //Alguns getlines repetidos pra pegar /n


        //Tipo == 1 significa que é livro impresso então é necessário criar um objeto do mesmo tipo
        if(tipo == 1){

            //Leio os campos exclusivos da classe

            string liv;
            getline(inFile, liv);
            split(liv, livrarias);
            
            int colunas;
            inFile >> colunas;

            Impresso *I = new Impresso(escritores, titulo, capitulos, ano, idioma, keywords, livrarias, colunas);

            //Insiro no vetor de Livros o ponteiro
            biblioteca.push_back(I);
        }

        //Tipo == 2 significa que é livro expresso então é necessário criar um objeto do mesmo tipo
        else if(tipo == 2){

            //Leio os campos exclusivos da classe

            string url;
            string formatoArquivo;


            getline(inFile, url);
            getline(inFile, formatoArquivo);

            Eletronico *E = new Eletronico(escritores, titulo, capitulos, ano, idioma, keywords, url, formatoArquivo);
            
            //Insiro no vetor de Livros o ponteiro
            biblioteca.push_back(E);
        }

        //Tipo == 3 significa que é AudioBook então é necessário criar um objeto do mesmo tipo
        else if(tipo == 3){

            //Leio os campos exclusivos da classe

            float duracao;
            inFile >> duracao;
            string formato;

            getline(inFile, formato);
            getline(inFile, formato);

            AudioBook *A = new AudioBook(escritores, titulo, capitulos, ano, idioma, keywords, duracao, formato);

            //Insiro no vetor de Livros o ponteiro
            biblioteca.push_back(A);
        }
    }

    //Após ler você vai escolher uma função e seguir como é pedido
    char op;

    cout << "Digite a funcao que deseja de 'b' ate 'l'\n";
    cin >> op;

    if(op == 'b'){
        string idioma;
        vector <Livro*> result;

        cout << "Digite um idioma\n";
        cin >> idioma;
        result = idiomaCatch(biblioteca, idioma);

        if((result.size())== 0){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{
            for(auto livro : result){
                cout << *livro;
            }
        }
    }

    if(op == 'c'){
        string formato;
        vector <Livro*> result;

        cout << "Digite um formato\n";
        cin >> formato;

        result = formatoCatch(biblioteca, formato);

        if((result.size())== 0){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{
            for(auto livro : result){
                cout << *livro;
            }
        }
        
    }

    if(op == 'd'){
        int qtd;
        vector <Livro*> result;

        cout << "Digite um numero de livrarias\n";
        cin >> qtd;

        result = numLivrariaCatch(biblioteca, qtd);

        if((result.size())== 0){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{

            for(int i = 0; i < result.size(); i++){
             
                Impresso *I;
                I = dynamic_cast<Impresso*>(result[i]);
                cout << I->getTitulo() << " | " << I->getLivrarias().size();
                cout << endl;
            }

        }
        
    }

    if(op == 'e'){
        string escritor;
        bool result;

        cout << "Digite o nome de um escritor\n";
        getline (cin, escritor);
        getline (cin, escritor);

        result = escritorCatch(biblioteca, escritor);

        if(result == false){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{
            cout << "Foi possivel encontrar\n";
        }
    }

    if(op == 'f'){
        string titulo;
        vector <Livro*> result;

        cout << "Digite o Titulo do livro\n";
        getline (cin, titulo);
        getline (cin, titulo);

        result = tituloCatch(biblioteca, titulo);

        if(result.size() == 0){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{
            for(auto livro : result){
                cout << *livro;
            }
        }
    }

    if(op == 'g'){
        vector <Livro*> result;
        vector <string> keywords;
        
        keywords = keywordCatch(biblioteca);

        if(keywords.size() == 0){
            cout << "Nao foi possivel encontrar nenhuma keyword\n";
        }
        else{
            for(auto i : keywords){
                cout <<i << ";";
            }
        }
    }

    if(op == 'h'){
        vector <Livro*> result;
        int capitulos;
        
        cout << "Digite a quantidade de capitulos\n";
        cin >> capitulos;

        result = numCapituloCatch(biblioteca, capitulos);

        if(result.size() == 0){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{
            for(auto livro : result){
                cout << *livro;
            }
        }
    }


    if(op == 'i'){
        vector<vector<Livro*>::iterator> vec;
        string titulo;

        Impresso *I;
        Eletronico *E;
        AudioBook *A;

        cout << "Digite o Titulo do livro\n";
        getline (cin, titulo);
        getline (cin, titulo);


        vec = returnIterators(biblioteca, titulo);

        for (auto it : vec) {
            if ((I = dynamic_cast<Impresso*>(*it)) != NULL) { 
                cout << *I;//escreve no terminal
            } else if ((E = dynamic_cast<Eletronico*>(*it)) != NULL) { 
                cout << *E;
            } else if ((A = dynamic_cast<AudioBook*>(*it)) != NULL) { 
                cout << *A;
            }
        }

        // for (auto it : vec) {
        //     cout << **it;
        // }

    }

    if(op == 'j'){       
        string option;

        cout << "Digite 'arquivo' ou 'terminal' para selecionar como deseja ver a lista dos livros\n";
        cin >> option;

        if(option == "arquivo"){
            allCatch(biblioteca, false);
        }
        else{
            allCatch(biblioteca, true);
        }

    }

    if(op == 'k'){
        int livros;
        string keyword;

        cout << "Digite uma keyword\n";
        cin >> keyword;

        livros = keywordSearch(biblioteca, keyword);

        if(livros == 0){
            cout << "Nao foi possivel encontrar nenhum livro\n";
        }
        else{
            cout << "Foi encontrado: " << livros << " livros\n";
        }
    }

    if(op == 'l'){
        Mmid mapeamento;
        mapeamento = mapea(biblioteca); 

        Mmid :: iterator iter;
        for(iter = mapeamento.begin(); iter != mapeamento.end(); ++ iter){
            cout << iter->first << " , " << (*iter->second);
        }
    }

    cout << endl;


    return 0;
}