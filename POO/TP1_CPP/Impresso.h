#ifndef IMPRESSO_H
#define IMPRESSO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Livro.h"

using namespace std;

class Impresso : public Livro{
    //Campos exclusivos de Impresso
    
    vector <string> livrarias;
    int colunas;

    public:
        //Construtor e destrutor
        Impresso();
        Impresso(vector <string>, string, vector <string>, int, string, vector <string>, vector <string>, int);
        virtual ~Impresso();

        //Metodos
        vector <string> getLivrarias() const;
        void setLivrarias(vector <string>);
        int getColunas() const;
        void setColunas(int);

        //Sobrecarga
        void serialize(ostream&) const;
        friend ostream& operator <<(ostream&, const Impresso&);
};

#endif