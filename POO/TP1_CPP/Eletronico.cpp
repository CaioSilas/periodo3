#include "Eletronico.h"

Eletronico :: Eletronico(){
}

//Construtor com Polimorfismo para evitar repetição de código
Eletronico :: Eletronico(vector <string> escritores, string titulo, vector <string> capitulos, int anoPublicacao, string idiomaOriginal, vector <string> keywords, string url, string formatoArquivo) : Livro(escritores, titulo, capitulos, anoPublicacao, idiomaOriginal, keywords){
    this->url = url;
    this->formatoArquivo = formatoArquivo;
}

Eletronico :: ~Eletronico(){
}



string Eletronico :: getUrl() const{
    return url;
}

void Eletronico :: setUrl(string url){
    this->url = url;
}

string Eletronico :: getFormatoArquivo() const{
    return formatoArquivo;
}
void Eletronico :: setFormatoArquivo(string formatoArquivo){
    this->formatoArquivo = formatoArquivo;
}


void Eletronico :: serialize(ostream& out) const{
    //Função que imprime igual pedido no enunciado

    //Chamamos o serialize de Livro para evitar repetição de código
    Livro::serialize(out);
    out << " | " << formatoArquivo;
}
ostream& operator <<(ostream & out, const Eletronico& eletronico){
    eletronico.serialize(out);
    out << endl;
    return out;
}