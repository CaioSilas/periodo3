#include "Livro.h"

using namespace std;

Livro :: Livro(){
}
Livro :: Livro(vector <string> escritores, string titulo, vector <string> capitulos, int anoPublicacao, string idiomaOriginal, vector <string> keywords){
    this->escritores = escritores;
    this->titulo = titulo;
    this->capitulos = capitulos;
    this->anoPublicacao = anoPublicacao;
    this->idiomaOriginal = idiomaOriginal;
    this->keywords = keywords;
}
Livro :: ~Livro(){
}

vector <string> Livro :: getEscritores() const {
    return escritores;
}
void Livro :: setEscritores(vector <string> escritores){
    this->escritores = escritores;
}

string Livro :: getTitulo() const{
    return titulo;
}
void Livro :: setTitulo(string titulo){
    this->titulo = titulo;
}

vector <string> Livro :: getCapitulos()const {
    return capitulos;
}
void Livro :: setCapitulos(vector <string> capitulos){
    this->capitulos = capitulos;
}
        
int Livro :: getAnoPublicacao()const {
    return anoPublicacao;
}
void Livro :: setAnoPublicacao(int anoPublicacao){
    this->anoPublicacao = anoPublicacao;
}

string Livro :: getIdiomaOriginal()const {
    return idiomaOriginal;
}
void Livro :: setIdiomaOriginal(string idiomaOriginal){
    this->idiomaOriginal = idiomaOriginal;
}

vector <string> Livro :: getKeywords()const {
    return keywords;
}
void Livro:: setKeywords(vector <string> keywords){
    this->keywords = keywords;
}


void Livro:: serialize(ostream& out) const{
    //Função que organizando o Out como pedido no enunciado

    string titulo = getTitulo();
    if(titulo.size() > 30){
        titulo.resize(30);
    } else {
        titulo.insert(titulo.end(), 30-titulo.size(), ' ');
    }
    vector <string> escritores = getEscritores();
    if (escritores[0].size() > 30){
        escritores[0].resize(30);
    } else {
        escritores[0].insert(escritores[0].begin(), 30-escritores[0].size(), ' ');
    }

    string idiomaOriginal = getIdiomaOriginal();

    if(idiomaOriginal.size() > 10){
        idiomaOriginal.resize(10);
    }
    else {
        idiomaOriginal.insert(idiomaOriginal.end(), 10-idiomaOriginal.size(), ' ');
    }


    vector <string> capitulos = getCapitulos();
    
    int tamCapitulos = capitulos.size();
    string str = to_string(tamCapitulos);
    //se caso for menor que 10 completar os dois caracteres com espaço
    if (tamCapitulos < 10){
        str.insert(str.begin(), ' ');
        str.insert(str.begin(), ' ');
    }
    //se caso for menor que 100
    else if (tamCapitulos < 100){
        str.insert(str.begin(), ' ');
    }

    vector <string> keywords = getKeywords();
    int tamKey = keywords.size();
    string tamKeyS = to_string(tamKey);
    if(tamKey < 10){
        tamKeyS.insert(tamKeyS.begin(), '0');
    }

    out << titulo << " | " << escritores[0] << " | " << idiomaOriginal << " | " << str << " | " << tamKeyS;
}


ostream& operator<<(ostream& out, const Livro& livro){
    livro.serialize(out);
    out << endl;
    return out;
}