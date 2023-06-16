#include "Impresso.h"

Impresso :: Impresso(){
}
//Construtor que utiliza o construtor da classe pai
Impresso :: Impresso(vector <string> escritores, string titulo, vector <string> capitulos, int anoPublicacao, string idiomaOriginal, vector <string> keywords, vector <string> livrarias, int colunas) : Livro(escritores, titulo, capitulos, anoPublicacao, idiomaOriginal, keywords){
    this->livrarias = livrarias;
    this->colunas = colunas;
}

Impresso :: ~Impresso(){
}

vector <string> Impresso :: getLivrarias() const{
    return livrarias;
}
void Impresso :: setLivrarias(vector <string> livrarias){
    this->livrarias = livrarias;
}

int Impresso :: getColunas() const{
    return colunas;
}
void Impresso :: setColunas(int colunas){
    this->colunas = colunas;
}

void Impresso :: serialize(ostream& out) const{
    //Função que organiza o out como pedido no enunciado

    //Chamo o serialize de livro para não repertir código
    Livro::serialize(out);

    vector <string> livrarias = getLivrarias();
    if(livrarias.size() == 0){
        out << " | Nenhuma";
    }
    else{
        out << " | " << livrarias[0];
    }

}

ostream& operator <<(ostream& out, const Impresso& impresso){
    impresso.serialize(out);
    out << endl;

    return out;
}