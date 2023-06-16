#ifndef AUDIOBOOK_H
#define AUDIOBOOK_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Livro.h"

using namespace std;

class AudioBook : public Livro{

private:
    //Campos exclusivos de AudioBook
    float duracao;
    string formatoAudio;

    public:
        //Construtores e destrutores
        AudioBook();
        AudioBook(vector <string>, string, vector <string>, int, string, vector <string>, float, string);
        virtual ~AudioBook();

        //Metodos
        float getDuracao() const;
        void setDuracao(float);
        string getFormatoAudio()const;
        void setFormatoAudio(string);

        //Sobrecarga
        void serialize(ostream&) const;
        friend ostream& operator <<(ostream &, const AudioBook&);
};

#endif