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
    int funcion, continuar;
    Menu mainz;

    do
    {
        cout << "Bienvenido a la biblioteca, seleccione que funcion desea llevar a cabo" << endl 
             << "1. Encontrar camino a un pasillo en especifico." << endl << "2. Consultar datos por pasillo." << endl
             << "3. Consultar libros por numero de hojas" << endl << "4. Correr pruebas automaticas" << endl
             << "[ADVERTENCIA] Lea con cuidado las instrucciones, si ingresa texto cuando se le pide numeros y viceversa"
             ", el programa presentara error" << endl
             << "Eleccion: ";

        cin >> funcion;
        cout << "\n";

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
        cout << "\nSi desea usar otras funciones, ingrese 1, de lo contrario ingrese 0: ";
        cin >> continuar;

        if(continuar == 0){
            flag= false;
        }
    } while (flag);
}