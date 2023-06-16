#ifndef LIVRO_H
#define LIVRO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Livro{

private:
    //Campos de Livro
    vector <string> escritores;
    string titulo;
    vector <string> capitulos;
    int anoPublicacao;
    string idiomaOriginal;
    vector <string> keywords;

    public:
        //Construtores e destrutor
        Livro();
        Livro(vector <string>, string, vector <string>, int, string, vector <string>);
        virtual ~Livro();
        
        //Metodos
        vector <string> getEscritores() const;
        void setEscritores(vector <string>);
        string getTitulo() const;
        void setTitulo(string);
        vector <string> getCapitulos() const;
        void setCapitulos(vector <string>);
        int getAnoPublicacao() const;
        void setAnoPublicacao(int);
        string getIdiomaOriginal() const;
        void setIdiomaOriginal(string);
        vector <string> getKeywords() const;
        void setKeywords(vector <string>);

        //Sobrecarga
        void serialize(ostream&) const;
        friend ostream& operator<<(ostream&, const Livro&);
};

#endif