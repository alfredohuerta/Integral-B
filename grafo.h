/**
 * @file grafo.h
 * @author Erick Alfredo García Huerta - A01708119
 * @brief Archivo que almacena dentro de un grafo los distintos pasillos de la bibliotec (strings), donde aplica una 
 * depth first search para devolver el camino a recorrer desde un pasillo inicial hasta uno objetivo.
 * @date 2021-11-29
 */
#ifndef GRAFO_H_
#define GRAFO_H_

#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph{
    private:
        int edgesList;
        int nodes;
        vector<int> *adjList;
    public:
        Graph();
        Graph(int);

        void loadGraphList(const string &, int, int);
        void addEdgeAdjList(int, int);
        string DFS(int, int, vector<string> &);
        void dfsHelper(int, int, stack<int> &, list<int> &, vector<vector<int>> &, stringstream &, vector<string> &);
        static void printPath(vector<vector<int>> &, int, int, stringstream &, vector<string> &);
        bool contains(list<int>, int);
		void sortAdjList();
};

/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph(){
    edgesList = nodes = 0;
	adjList= {};
}

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param n valor del nodo que representa la id del pasillo.
 */
Graph::Graph(int n){
    nodes = n;
	adjList = new vector<int>[nodes];
	edgesList= 0;
}

/**
 * @brief Método que lee el archivo de texto que contiene todas las conecciones entre los nodos y carga estas relaciones
 * en la lista adjunta.
 * 
 * @param file_name nombre del archivo que contien las conecciones entre los nodos
 * @param a valor del nodo
 * @param b valor del nodo
 */
void Graph::loadGraphList(const string &file_name, int a, int b){
	nodes = a;
    adjList = new vector<int>[nodes];

    string line;
    ifstream archivo(file_name);
    int u, v;
    if (archivo.is_open()) {
        while (getline(archivo, line)) {
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(4, 1));
            addEdgeAdjList(u, v);
        }
        archivo.close();
	} else{
		cout << "Unable to open file";
	}
}

/**
 * @brief Método que asigna nuevos nodos en el grafo
 * 
 * @param u valor del nodo
 * @param v valor del nodo
 */
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

/**
 * @brief función que llama al dfs y carga los demás datos necesarios en otras funciones auxiliares.
 * 
 * @param start nodo donde se inicia
 * @param goal nodo al que se quiere ir
 * @param pasillos vector que ayuda a relacionar los nombres de los pasillos con su valor.
 * @return string camino que se debe recorrer para llegar al nodo objetivo.
 */
string Graph::DFS(int start, int goal, vector<string> &pasillos){
	stringstream aux;

	stack <int> st;
	list <int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1, -1));
	st.push(start);

	dfsHelper(start, goal, st, visited, paths, aux, pasillos);
	printPath(paths, start, goal, aux, pasillos);

	return aux.str();
}

/**
 * @brief Función que lleva a cabo el dfs.
 * 
 * @param current hubicación actual de la búsqueda
 * @param goal nodo al que se quiere ir
 * @param st stack donde se guardará momentaneamente el valor actual
 * @param visited lista de nodos visitados
 * @param paths registro del camino que se ha llevado
 * @param aux stringstream que imprimirá los datos en caso de encontrarse un camino válido
 * @param pasillos lista de nombre de los pasillos para hacer la relación entre valor y nombre del pasillo.
 */
void Graph::dfsHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths, stringstream &aux, vector<string> &pasillos){
	if(current == goal){
		return;
	} else if(st.empty()){
		cout << "No se encontró camino." << endl;
		return;
	} else{
		current= st.top();
		st.pop();
		visited.push_back(current);
		for(int i= 0; i < adjList[current].size(); i++){
			if(!contains(visited, adjList[current][i])){
				st.push(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
			}
		}
		dfsHelper(current, goal, st, visited, paths, aux, pasillos);
	}
}

/**
 * @brief Método que imprime el camino a recorrer para llegar al nodo objetivo una vez se encuentra una ruta válida
 * 
 * @param paths camino recorrido
 * @param start nodo donde se inicia
 * @param goal nodo donde se termina el camino
 * @param aux stringstream que servirá para imprimir los datos
 * @param pasillos lista de nombre de los pasillos para hacer la relación entre el nombre del pasillo y su valor como nodo.
 */
void Graph::printPath(vector<vector<int>> &paths, int start, int goal, stringstream &aux, vector<string> &pasillos){
	int node= paths[goal][0];

	stack<int> alReves;
	alReves.push(goal);

	while(node != start){
		alReves.push(node);
		node= paths[node][0];
	}

	alReves.push(start);
	while(!alReves.empty()){
		aux << pasillos[alReves.top()];
		alReves.pop();
		if(!alReves.empty()){
			aux << " ";
		}
	}
}

/**
 * @brief Método que busca si un nodo se encuentra en la lista de nodos visitados.
 * 
 * @param lista lista de nodos visitados.
 * @param node nodo a buscar en la lista de visitados
 * @return true se encuentra en la lista de nodos visitados
 * @return false no se encuentra en la lista de nodos visitados
 */
bool Graph::contains(list<int> lista, int node){
	list<int>::iterator it;

	it= find(lista.begin(), lista.end(), node);

	if(it != lista.end()){
		return true;
	} else{
		return false;
	}
}

/**
 * @brief función que ordena los nodos de la lista de adjacencia.
 * 
 */
void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(),adjList[i].end());
	}
}


#endif