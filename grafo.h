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

Graph::Graph(){
    edgesList = nodes = 0;
	adjList= {};
}

Graph::Graph(int n){
    nodes = n;
	adjList = new vector<int>[nodes];
	edgesList= 0;
}

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

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

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

void Graph::dfsHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths, stringstream &aux, vector<string> &pasillos){
	if(current == goal){
		cout << "Se encontro un camino. ";
	} else if(st.empty()){
		cout << "No se encontró." << endl;
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

void Graph::printPath(vector<vector<int>> &paths, int start, int goal, stringstream &aux, vector<string> &pasillos){
	aux << "Recorre comenzando por: ";
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

bool Graph::contains(list<int> lista, int node){
	list<int>::iterator it;

	it= find(lista.begin(), lista.end(), node);

	if(it != lista.end()){
		return true;
	} else{
		return false;
	}
}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(),adjList[i].end());
	}
}


#endif