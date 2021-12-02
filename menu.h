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

/**
 * @brief Función que convierte la Key
 * 
 * @complejidad: O(n) por la presencia de un ciclo for.
 * 
 * @param s Llave de la hash table
 * @return unsigned int llave convertida
 */
unsigned int my_Hash(const string s) {
    unsigned int acum = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        acum += (int) s[i];
    }
    return acum;
}

/**
 * @brief Clase de apoyo que crea los pasillos de la biblioteca y que será almacenada dentro de la clase Menu, además de 
 * que facilita el acceso a los distintos datos necesarios, como los libros.
 */
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

/**
 * @brief Construct a new Pasillo:: Pasillo object
 * 
 * @complejidad: O(n) por la presencia de un ciclo for.
 * 
 * @param id identificador del pasillo
 * @param nombre nombre del pasillo
 * @param nombres nombres de las obras almacenadas en el pasillo
 * @param nlibros numero de libros en el pasillo
 */
Pasillo::Pasillo(int id, string nombre, vector<vector<string>> nombres, int nlibros){
    for(int i= 0; i < nlibros; i++){
        nombreLibros.push_back(nombres[id][i]);
    }

    nombreP= nombre;
    numeroLibros= nlibros;
    contenido= crearLibros(1, nombreLibros, nombre);
}

/**
 * @brief Función que asigna sus datos a las estructuras tipo libro que serán almacenadas en el pasillo
 * 
 * @complejidad: O(n) por la presencia de un ciclo for.
 * 
 * @param id identificador del libro
 * @param titulos títulos de los libros
 * @param ubi pasillo en el que se encuetran los libros
 * @return vector<struct Libros> vector que contiene las estructuras tipo libros.
 */
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
/**
 * @brief función que regresa el nombre del pasillo
 * 
 * @complejidad: O(1)
 * 
 * @return string nombre del pasillo
 */
string Pasillo::getNombre(){
    return nombreP;
}

/**
 * @brief Funcion que regresa la cantidad de libros en el pasillo
 * 
 * @complejidad: O(1)
 * 
 * @return int numero de libros en el pasillo
 */
int Pasillo::getnumeroLibros(){
    return numeroLibros;
}

/**
 * @brief Función que regresa el vector completo de los libros almacenados en el pasillo
 * 
 * @complejidad: O(1)
 * 
 * @return vector<struct Libros> estructuras tipo libro almacenadas en el pasillo
 */
vector<struct Libros> Pasillo::getLibros(){
    return contenido;
}

/**
 * @brief Función que recolecta los títulos de los libros almacenados en el pasillo.
 * 
 * @complejidad: O(n) por la presencia de un ciclo for para la obtención de los títulos
 * 
 * @return string títulos de los libros del pasillo.
 */
string Pasillo::getTitulos(){
    stringstream aux;

    for(int i= 0; i < contenido.size(); i++){
        aux << contenido[i].nombre << " ";
    }

    return aux.str();
}

/**
 * @brief Clase que controla las llamadas a las distintas funciones del programa, además de que contien los datos necesarios
 * para la creación de las estructuras necesitadas.
 */
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

/**
 * @brief Construct a new Menu:: Menu object
 */
Menu::Menu(){
    pasillos= crearPasillos();
}
 
/**
 * @brief Función que construye objetos tipo Pasillo que serán almacenados en el menu para ser asignados cuando sea necesario
 * en las distintas estructuras de datos
 * 
 * @complejidad: O(n) por la presencia de un ciclo for 
 * 
 * @return vector<Pasillo> arreglo de Pasillos que facilita su asignación en las demás estructuras de datos
 */
vector<Pasillo> Menu::crearPasillos(){
    vector<Pasillo> temp;

    for(int i= 1; i < nombrePasillos.size(); i++){
        Pasillo basic(i, nombrePasillos[i], todos, 5);
        temp.push_back(basic);
    }

    return temp;
}

/**
 * @brief Método que cosntruye y maneja la estructura del grafo.
 * 
 * @complejidad_individual: O(n) por la presencia de un ciclo for para la presentación de los nombres de los pasillos.
 * @complejidad_estructura: O(n*m) ya que se calcula en base a la cantidad de arcos y vértices en el grafo.
 * Se realiza un análisis más detallado en grafo.h
 */
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

/**
 * @brief Método que construye y maneja la estructura del hash table.
 * 
 * @complejidad_individual: O(n) por la presencia de ciclos for para el manejo de la asignación de datos en la tabla hash y la 
 * presentación de los nombres de los pasillos. Pero al no estar anidados quedan como O(n)
 * @complejidad_estructura: O(n) debido a que en el peor de los casos, la función deberá recorrer todos espacios de la tabla
 * antes de encontrar el espacio donde la key debe ir.
 * Se realiza un análisis más exhaustivo en hash.h
 */
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

/**
 * @brief Método que construye y maneja el AVL
 * 
 * @complejidad_individual: O(n) por la presencia de ciclos for para la presentación de los pasillos de la biblioteca y 
 * la construcción del avl, pero al no estar anidados quedan como O(n).
 * @complejidad_estructura: al ser un AVL, la complejidad de los tiempos de búsqueda es de O(log n), ya conforme avanza
 * la búsqueda, se va descartando la mitad de los datos.
 * Se realiza un análisis más exahustivo en grafo.h
 */
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

/**
 * @brief Método que genera casos de prueba para cada una de las funciones y compara los resultados.
 * 
 * @complejidad: O(n) debido a la precencia de ciclos for no anidados.
 */
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