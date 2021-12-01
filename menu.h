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
        vector<struct Libros> crearLibros(int, vector<string>, string);

        string getNombre();
        int getnumeroLibros();
        vector<struct Libros> getLibros();
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

string Pasillo::getNombre(){
    return nombreP;
}

int Pasillo::getnumeroLibros(){
    return numeroLibros;
}

vector<struct Libros> Pasillo::getLibros(){
    return contenido;
}

class Menu{
    private:
        vector<Pasillo> pasillos;
        vector<string> nombrePasillos= {"Recepcion", "Poesia", "Medicina", "Ciencias naturales", "Fisica", "Computacion", 
                                        "Politica"};

        vector<string> nombreLibrosP= {"Iliada", "La Divina Comedia", "Nostalgia de la Muerte", "Poesia en movimiento", 
                                      "Poesia Reunida - Ali Chumacero", "100 Poemas de Amor y una Cancion desesperada"};

        vector<string> nombreLibrosM= {"Anatomia basica", "Harrison - Medicina interna", "Histología", "Epidemiologia", 
                                       "Medicina de bolsillo", "Fisiologia médica"};

        vector<string> nombreLibrosCN= {"Ciencias Natuales - SEP", "Zoologia basica", "El Origen de las especies", 
                                        "Ciencias Naturales 1", "Somos agua", "Problemas resueltos de quimica"};

        vector<string> nombreLibrosF= {"Breve historia del tiempo", "La teoria del todo", "Agujeros negros y tiempo curvo"
                                       "La teoria de la relatividad", "Cosmos", "Fundamentos de la fisica"};

        vector<string> nombreLibrosC= {"Cracking the coding interview", "Compiladores", "Software libre para una sociedad libre",
                                       "Deep learning with Python", "Sistemas operativos modernos", "Python a fondo"};

        vector<string> nombreLibrosPol= {"El principe", "El arte de la guerra", "La consitucion mexicana", 
                                         "Asi hablo Zaratustra", "Dialogos socraticos", 
                                         "Dialogo en el infierno entre Maquiavelo y Montesquieu"};

        vector<vector<string>> todos= {{"Recepcion"}, {nombreLibrosP}, {nombreLibrosM}, {nombreLibrosCN}, 
                                              {nombreLibrosF}, {nombreLibrosC}, {nombreLibrosPol}};
        vector<Pasillo> crearPasillos();
    public:
        Menu();
        void crearGrafo();
        void crearHash();
        void usarAVL();
};

Menu::Menu(){
    pasillos= crearPasillos();
}
 
vector<Pasillo> Menu::crearPasillos(){
    vector<Pasillo> temp;

    for(int i= 1; i < nombrePasillos.size(); i++){
        Pasillo basic(i, nombrePasillos[i], todos, 5);
        temp.push_back(basic);
    }

    return temp;
}

void Menu::crearGrafo(){
    Graph grafo;
    int inicio, final;

    grafo.loadGraphList("Pasillos.txt", 18, 18);

    cout << "Estos son los pasillos de la biblioteca: " << endl;
    for(int i= 1; i < nombrePasillos.size(); i++){
        cout << i << " " << nombrePasillos[i] << endl;
    }

    cout << "Ingrese su pasillo actual: ";
    cin >> inicio;
    cout << nombrePasillos[inicio] << endl;
    cout << endl << "Ingrese el pasillo al que desea ir: ";
    cin >> final;
    cout << nombrePasillos[final] << endl;

    cout << grafo.DFS(inicio, final, nombrePasillos) << endl;
    
}

void Menu::crearHash(){
    cout << "Crear Hash" << endl;
}

void Menu::usarAVL(){
    cout << "Crear arbol AVL" << endl;
    AVLLibros avl;
    vector<struct Libros> temp;
    int eleccionPasillo, eleccion;
    bool flag= true;

    do
    {
        cout << "Ingrese el pasillo del que quiere extraer los libros: ";
        cin >> eleccionPasillo;

        temp= pasillos[eleccionPasillo].getLibros();
        
        for(int i= 0; i < 5; i++){
            avl.add(temp[i]);
        }

        cout << endl << "Ingrese cómo desea imprimir sus datos: \n" << "1. inorder\n 2.Preorder\n Esperando... ";
        cin >> eleccion;

        switch (eleccion)
        {
        case 1:
            cout << endl << pasillos[eleccionPasillo].getNombre() << endl;
            cout << endl << "Inorder: " << avl.inorder() << endl;
            break;
        case 2:
            cout << endl << pasillos[eleccionPasillo].getNombre() << endl;
            cout << endl << "Preorder: " << avl.preorder() << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        avl.removeAll();

    } while (flag);
}

#endif