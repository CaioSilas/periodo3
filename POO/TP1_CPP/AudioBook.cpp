#include "AudioBook.h"


AudioBook :: AudioBook(){
}
//Contrutor que utiliza polimorfismo para evitar repetição de código
AudioBook :: AudioBook(vector <string> escritores, string titulo, vector <string> capitulos, int anoPublicacao, string idiomaOriginal, vector <string> keywords, float duracao, string formatoAudio) 
    : Livro(escritores, titulo, capitulos, anoPublicacao, idiomaOriginal, keywords) {
        this->duracao = duracao;
        this->formatoAudio = formatoAudio;
}
AudioBook :: ~AudioBook(){
}

float AudioBook :: getDuracao() const{
    return duracao;
}
void AudioBook :: setDuracao(float duracao){
    this->duracao = duracao;
}

string AudioBook :: getFormatoAudio() const{
    return formatoAudio;
}
void AudioBook :: setFormatoAudio(string formatoAudio){
    this->formatoAudio = formatoAudio;
}

void AudioBook :: serialize(ostream& out) const{
    //Função que altera o out como pedido no enunciado
    
    //Chamando o serialize de Livro para evitar repetição de código
    Livro::serialize(out);

    out << " | " << fixed << setprecision(2) << duracao;
}
ostream& operator <<(ostream & out, const AudioBook& audioBook){
    audioBook.serialize(out);
    out << endl;

    return out;
}