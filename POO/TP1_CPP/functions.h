#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//Função principal com todos as funções utilizadas no main 

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <typeinfo>

#include "Livro.h"
#include "Impresso.h"
#include "Eletronico.h"
#include "AudioBook.h"

using namespace std;

#include <string> 
#include <algorithm> 
#include <iterator> 
#include <map>

typedef std::multimap<string, Livro*>Mmid;

//Funções do enunciado de B à L
vector <Livro*> idiomaCatch(vector <Livro*>, string);
vector <Livro*> formatoCatch(vector <Livro*>, string);
vector <Livro*> numLivrariaCatch(vector <Livro*>, int);
bool escritorCatch(vector <Livro*>, string);
vector <Livro*> tituloCatch(vector <Livro*>, string);
vector <string> keywordCatch(vector <Livro*>);
vector <Livro*> numCapituloCatch(vector <Livro*>, int);
vector<vector<Livro*>::iterator> returnIterators(vector <Livro*>&, string);
void allCatch(vector <Livro*>, bool);
int keywordSearch(vector <Livro*>, string);
Mmid mapea(vector<Livro*>);

#endif