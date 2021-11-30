#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "grafo.h"
#include "hash.h"
#include "libros.h"
//#include "avl.h"

using namespace std;

unsigned int my_Hash(const string s) {
    unsigned int acum = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        acum += (int) s[i];
    }
    return acum;
}

class Pasillo{
    private:
        string nombreP;
        int numeroLibros;
        vector<Libros> contenido;
    public:
        Pasillo(string, int);
        string getNombre();
        int getnumeroLibros();
};

Pasillo::Pasillo(string nombre, int libros){
    nombre= nombre;
    numeroLibros= libros;
}


class Menu{
    private:
        vector<string> pasillos= {"Recepcion", "Poesia", "Medicina", "Ciencias naturales", "Fisica", "Computacion", "Politica"};
        string nombreBiblioteca;
    public:
        Menu();
};

Menu::Menu(){
    nombreBiblioteca= "Estructura de datos y algoritmos fundamentales";
    

    Hash<string, vector<Libros>> tabla(pasillos.size(), string("Null"), my_Hash);
}

#endif