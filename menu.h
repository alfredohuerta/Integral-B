/**
 * @file menu.h
 * @author Erick Alfredo García Huerta
 * @brief Archivo que controla las distintas funcionalidades del programa. Manda a llamar las estructuras, recibe datos
 * e imprime resultados, así como genera casos de prueba para los mismos.
 * @date 2021-12-01
 */
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
        vector<int> paginas= {521, 23, 145, 482, 73, 100};
        
        string nombreP;
        vector<string> nombreLibros; 
        int numeroLibros;
    public:
        Pasillo(int, string, vector<vector<string>>, int);
        vector<struct Libros> crearLibros(int, vector<string>, string);

        string getNombre();
        int getnumeroLibros();
        vector<struct Libros> getLibros();
        string getTitulos();
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

    for(int j= 0; j < titulos.size(); j++){
        lirbo.id= i;
        lirbo.numeroDeHojas= paginas[j];
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

string Pasillo::getTitulos(){
    stringstream aux;

    for(int i= 0; i < contenido.size(); i++){
        aux << contenido[i].nombre << " ";
    }

    return aux.str();
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

        vector<vector<string>> todos= {{"Recepcion", " ", " ", " ", " ", " "}, {nombreLibrosP}, {nombreLibrosM}, {nombreLibrosCN}, 
                                              {nombreLibrosF}, {nombreLibrosC}, {nombreLibrosPol}};
        vector<Pasillo> crearPasillos();
    public:
        Menu();
        void usarGrafo();
        void usarHash();
        void usarAVL();
        void pruebasAutomaticas();
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

void Menu::usarGrafo(){
    Graph grafo;
    int inicio, final;

    grafo.loadGraphList("Pasillos.txt", 18, 18);

    cout << "Estos son los pasillos de la biblioteca: " << endl;
    for(int i= 1; i < nombrePasillos.size(); i++){
        cout << i << " " << nombrePasillos[i] << endl;
    }

    cout << "Ingrese el numero de su pasillo actual: ";
    cin >> inicio;
    cout << "Se encuentra en: " << nombrePasillos[inicio] << endl;
    cout << endl << "Ingrese el pasillo al que desea ir: ";
    cin >> final;
    cout << "Desea ir a: " << nombrePasillos[final] << endl;

    cout << "Utilice el siguiente camino: " << grafo.DFS(inicio, final, nombrePasillos) << endl;
    
}

void Menu::usarHash(){
    stringstream aux;
    int continuar; 
    string pasillo;
    bool flag= true;

    Hash<string, string> hash(10, string("empty"), my_Hash);

    for(int i= 1; i < nombrePasillos.size(); i++){
        aux << pasillos[i-1].getTitulos();

        hash.put(nombrePasillos[i], aux.str());
                
        aux.str(string());
    }

    do
    {
        cout << "Pasillos de la biblioteca: " << endl;
        for (int i= 1; i < nombrePasillos.size(); i++){
            cout << nombrePasillos[i] << endl;
        }
        cout << "Ingrese el nombre del pasillo al que quiere acceder [Advertencia: hagalo sin acentos y comenzando las" 
                "palabras con mayusculas]: ";
        cin >> pasillo;

        cout << endl << "Contenido del pasillo: " << hash.get(pasillo) << endl;
        cout << "Si desea buscar los datos de otro pasillo, ingrese 1, de lo contrario ingrese 0: ";
        cin >> continuar;

        if(continuar == 0){
            flag= false;
        }

    } while (flag);
    
}

void Menu::usarAVL(){
    AVLLibros avl;
    vector<struct Libros> temp;
    int eleccionPasillo, eleccion, continuar;
    bool flag= true;

    do
    {
        cout << "Pasillos de la biblioteca: " << endl;
        for (int i= 1; i < nombrePasillos.size(); i++){
            cout << nombrePasillos[i] << endl;
        }

        cout << "Ingrese el pasillo del que quiere extraer los libros: ";
        cin >> eleccionPasillo;

        temp= pasillos[eleccionPasillo].getLibros();
        
        for(int i= 0; i < 5; i++){
            avl.add(temp[i]);
        }

        cout << endl << "Ingrese como desea imprimir sus datos: \n" << "1. inorder\n 2.Preorder\n Esperando... ";
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

        cout << "Si desea buscar los datos de otro pasillo, ingrese 1, de lo contrario ingrese 0: ";
        cin >> continuar;

        if(continuar == 0){
            flag= false;
        }

        avl.removeAll();

    } while (flag);
}

void Menu::pruebasAutomaticas(){
    cout << endl << "Prueba Grafo:" << endl;
    stringstream ssans;
    string test, ans;

    Graph grafoT;

    ans= "Poesia Politica Computacion Medicina";
    grafoT.loadGraphList("Pasillos.txt", 18, 18);
    test= grafoT.DFS(1, 2, nombrePasillos);

    if(!ans.compare(test)){
        cout << "SUCCESS" << endl;
    } else{
        cout << "FAIL" << endl;
    }
    cout << "Esperado: " << ans << endl;
    cout << "Obtenido: " << test << endl;

    cout << endl << "Prueba Hash" << endl;
    Hash<string, string> hashT(10, string("empty"), my_Hash);
    stringstream aux;

    for(int i= 1; i < nombrePasillos.size(); i++){
        aux << pasillos[i-1].getTitulos();

        hashT.put(nombrePasillos[i], aux.str());
                
        aux.str(string());
    }

    ssans << pasillos[0].getTitulos();

    if(!ssans.str().compare(hashT.get("Poesia"))){
        cout << "SUCCESS" << endl;
    } else{
        cout << "FAIL" << endl;
    }

    cout << "Esperado: " << ssans.str() << endl;
    cout << "Obtenido: " << hashT.get("Poesia") << endl;

    cout << endl << "Prueba AVL" << endl;
    AVLLibros avl;
    vector<struct Libros> temp;
    string ans2, test2;

    temp= pasillos[0].getLibros();
    
    for(int i= 0; i < 5; i++){
        avl.add(temp[i]);
    }

    ans= "[(La Divina Comedia 23) (Poesia Reunida - Ali Chumacero 73) (Nostalgia de la Muerte 145) "
         "(Poesia en movimiento 482) (Iliada 521)]";
    test= avl.inorder();

    ans2= "[(Nostalgia de la Muerte 145) (La Divina Comedia 23) (Poesia Reunida - Ali Chumacero 73) (Iliada 521) "
          "(Poesia en movimiento 482)]";
    test2= avl.preorder();

    if(!ans.compare(test) && !ans2.compare(test2)){
        cout << "SUCCESS" << endl;
    } else{
        cout << "FAIL" << endl;
    }

    cout << "Esperado [inorder]: " << ans << endl;
    cout << "Obtenido [inorder]: " << test << endl;
    cout << "Esperado [preorder]: " << ans2 << endl;
    cout << "Obtenido [preorder]: " << test2 << endl;
}

#endif