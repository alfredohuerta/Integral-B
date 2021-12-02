/**
 * @file main.cpp
 * @author Erick Alfredo García Huerta - A01708119
 * @brief Proyecto que busca representar una biblioteca donde se pueden navegar entre los pasillos, los cuales tienen
 * objetos tipo pasillo, objetos tipo libro, los cuales están ordenados en un avl.
 * @date 2021-11-29
 * 
 */

#include <iostream>
#include <cstring>

#include "menu.h"

using namespace std;

int main(){
    bool flag= true;
    int funcion;
    Menu mainz;

    do
    {
        cout << "Bienvenido a la biblioteca, seleccione que funcion desea llevar a cabo" << endl 
             << "1. Encontrar camino a un pasillo en especifico." << endl << "2. Consultar datos por pasillo." << endl
             << "3. Consultar libros por numero de hojas" << endl << "4. Correr pruebas automaticas" << endl 
             << "Eleccion: ";

        cin >> funcion;

        switch (funcion)
        {
        case 1:
            mainz.usarGrafo();
            break;
        case 2:
            mainz.usarHash();
            break;
        case 3:
            mainz.usarAVL();
            break;
        case 4:
            mainz.pruebasAutomaticas();
            break;
        
        default:
            cout << "Ingrese un valor valido" << endl;
            break;
        }
    } while (flag);
}