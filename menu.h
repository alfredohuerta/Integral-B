#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

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
        Pasillo(int, string, vector<vector<string>>, int);
        string getNombre();
        int getnumeroLibros();
        vector<struct Libros> crearLibros(int, vector<string>, string);
};

Pasillo::Pasillo(int id, string nombre, vector<vector<string>> nombres, int nlibros){
    for(int i= 0; i < nlibros; i++){
        nombreLibros.push_back(nombres[id][i]);
    }

    nombreP= nombre;
    numeroLibros= nlibros;
    contenido= crearLibros(1, nombreLibros, nombre);
}

vector<struct Libros> Pasillo::crearLibros(int id, vector<string> titulos, string ubi){
    Libros lirbo;
    vector<struct Libros> temp;
    int i= 0;
    int paginas= rand() % 500 + 100;

    for(int j= 0; j < titulos.size(); j++){
        lirbo.id= i;
        lirbo.numeroDeHojas= paginas;
        lirbo.nombre= titulos[j];
        lirbo.ubicacion= ubi;

        temp.push_back(lirbo);
        i++;
    }

    return temp;
}

class Menu{
    private:
        vector<Pasillo> pasillos;
        vector<string> nombrePasillos= {"Recepcion", "Poesia", "Medicina", "Ciencias naturales", "Fisica", "Computacion", 
                                        "Politica"};

        vector<string> nombreLibrosP= {"Iliada", "La Divina Comedia", "Nostalgia de la Muerte", "Poesía en movimiento", 
                                      "Poesía Reunida - Alí Chumacero", "100 Poemas de Amor y una Canción desesperada"};

        vector<string> nombreLibrosM= {"Anatomía básica", "Harrison - Medicina interna", "Histología", "Epidemiología", 
                                       "Medicina de bolsillo", "Fisiologia médica"};

        vector<string> nombreLibrosCN= {"Ciencias Natuales - SEP", "Zoología básica", "El Origen de las especies", 
                                        "Ciencias Naturales 1", "Somos agua", "Problemas resueltos de química"};

        vector<string> nombreLibrosF= {"Breve historia del tiempo", "La teoría del todo", "Agujeros negros y tiempo curvo"
                                       "La teoría de la relatividad", "Cosmos", "Fundamentos de la física"};

        vector<string> nombreLibrosC= {"Cracking the coding interview", "Compiladores", "Software libre para una sociedad libre",
                                       "Deep learning with Python", "Sistemas operativos modernos", "Python a fondo"};

        vector<string> nombreLibrosPol= {"El principe", "El arte de la guerra", "La consitución mexicana", 
                                         "Así habló Zaratustra", "Dialogos socráticos", 
                                         "Dialogo en el infierno entre Maquiavelo y Montesquieu"};

        vector<vector<string>> todos= {{"Recepcion"}, {nombreLibrosP}, {nombreLibrosM}, {nombreLibrosCN}, 
                                              {nombreLibrosF}, {nombreLibrosC}, {nombreLibrosPol}};
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
        for(int j= 0; j < 5; j++){
            Pasillo basic(i, nombrePasillos[i], todos, 5);
            temp.push_back(basic);
        }
    }

    return temp;
}

#endif