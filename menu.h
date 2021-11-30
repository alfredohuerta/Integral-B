#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "libros.h"
#include "grafo.h"
#include "hash.h"
#include "avl.h"

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
        vector<Libros>  contenido;
        
        string nombreP;
        vector<string> nombreLibros; 
        int numeroLibros;
    public:
        Pasillo(string, vector<string>, int);
        string getNombre();
        int getnumeroLibros();
        vector<struct Libros> crearLibros(int, int, vector<string>, string);
};

Pasillo::Pasillo(string nombre, vector<string> nombres, int nlibros){
    nombreP= nombre;
    nombreLibros= nombres;
    numeroLibros= nlibros;
    contenido= crearLibros(1, 100, nombreLibros, nombre);
}

vector<struct Libros> Pasillo::crearLibros(int id, int pag, vector<string> nombres, string ubi){
    Libros lirbo;
    vector<struct Libros> temp;
    int i= 0;

    for(int j= id; id < id+nombres.size(); j++){
        lirbo.id= j;
        lirbo.numeroDeHojas= (((pag*3)+1)-5);
        lirbo.nombre= nombres[i];
        lirbo.ubicacion= ubi;

        temp.push_back(lirbo);
        i++;
    }

    return temp;
}

class Menu{
    private:
        vector<Pasillo> pasillos;
        vector<string> nombrePasillos= {"Recepcion", "Poesia", "Medicina", "Ciencias naturales", "Fisica", "Computacion", "Politica"};
        vector<string> nombreLibros= {"Iliada", "La Divina Comedia", "Nostalgia de la Muerte", "Poesía en movimiento", 
                                      "Poesía Reunida - Alí Chumacero", "100 Poemas de Amor y una Canción desesperada", 
                                      "La Eneida"};
    public:
        vector<Pasillo> crearPasillos();

        Menu();
};

Menu::Menu(){
    pasillos= crearPasillos();
}
 
vector<Pasillo> Menu::crearPasillos(){
    vector<Pasillo> temp;

    for(int i= 1; i < nombrePasillos.size(); i++){
        Pasillo basic(nombrePasillos[i], nombreLibros, nombreLibros.size());
        temp.push_back(basic);
    }
    return temp;
}

#endif