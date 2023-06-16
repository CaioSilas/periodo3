#ifndef ELETRONICO_H
#define ELETRONICO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Livro.h"

using namespace std;

class Eletronico : public Livro{

    //Campos exclusivos de Eletronico
    string url;
    string formatoArquivo;
    
    public:

        //Construtores e destrutores
        Eletronico();
        Eletronico(vector <string>, string, vector <string>, int, string, vector <string>, string, string);
        virtual ~Eletronico();

        //Metodos
        string getUrl() const;
        void setUrl(string);
        string getFormatoArquivo() const;
        void setFormatoArquivo(string);

        //Sobrecarga
        void serialize(ostream&) const;
        friend ostream& operator <<(ostream &, const Eletronico&);
};
#endif