/**
 * @file hash.h
 * @author Erick Alfredo García Huerta
 * @brief Programa que almacena los datos de los libros que se encuentran en un pasillo en una tabla hash, donde el nombre
 * del pasillo es la key, todo esto funcionando a través de una validación cuadrática.
 * @date 2021-11-29
 */
#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <class Key, class Value>
class Hash{
    private:
        unsigned int (*func) (const Key);
        unsigned int size;
        unsigned int count;

        Key *keys;
        Key initialValue;
        Value *values;

        long indexOf(const Key) const;
    public:
        Hash(unsigned int, Key, unsigned int (*f) (const Key));
        ~Hash();
        bool full() const;
        void clear();
        std::string toString() const;

        void put(Key, Value);
        Value get(const Key);
};

/**
 * @brief Construct a new Hash < Key,  Value>:: Hash object
 * 
 * @complejidad: O(n) por la presencia de ciclos for no anidados dependientes del tamaño del arreglo.
 * 
 * @tparam Key llave para acceder a la hash table
 * @tparam Value datos ingresados en la hash table
 * @param tam tamaño de la hash table
 * @param init valor inicial de la hash table
 * @param f función externa que ayuda con la llave
 */
template <class Key, class Value>
Hash <Key, Value>::Hash(unsigned int tam, Key init, unsigned int (*f) (const Key)){
	size = tam;
	keys = new Key[size];
	
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];
	
	for (int j = 0; j  < tam; j++){
		values[j]= " ";
    }

	func = f;
	count = 0;
}

/**
 * @brief Destroy the Hash < Key,  Value>:: Hash object
 * 
 * @complejidad: O(1) no hay ningún ciclo
 * 
 * @tparam Key llave para acceder a la hash table que se borrarán
 * @tparam Value valores dentro de la hash table que se borrarán
 */
template <class Key, class Value>
Hash <Key, Value>::~Hash(){
    delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;
}

/**
 * @brief Función que ayuda a encontrar la posición de los datos en la tabla haciendo uso de la función auxiliar y la
 * llave para encontrar el índice
 * 
 * @complejidad: O(n) debido a la presencia de un ciclo for dependiente del tamaño del arreglo.
 * 
 * @tparam Key llave para acceder a los datos de la tabla hash
 * @tparam Value valor dentro de la tabla hash
 * @param k llave
 * @return long posición del valor en la tabla hash
 */
template <class Key, class Value>
long Hash<Key, Value>::indexOf(const Key k) const{
	unsigned int i, start;

	start = i = func(k) % size;
	for(int j= 0; j < size; j++){
		if (keys[i] == k) {
			return i;
		}
		i = (start + j*j) % size;
	}
	return -1;
}

/**
 * @brief Función que valida si la tabla está llena o no
 * 
 * @complejidad: O(1) no hay ningún ciclo
 * 
 * @tparam Key llave para acceder a los valores
 * @tparam Value valores dentro de la tabla
 * @return true está llena
 * @return false está vacía
 */
template <class Key, class Value>
bool Hash<Key, Value>::full() const {
	return (count > size);
}

/**
 * @brief Función que devuelve a sus valores iniciales a las llaves de la tabla
 * 
 * @complejidad: O(n) debido a la presencia de un ciclo for dependiente del tamaño del arreglo.
 * 
 * @tparam Key llave para acceder a los datos del hash
 * @tparam Value valores dentro de la tabla
 */
template <class Key, class Value>
void Hash<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}

/**
 * @brief Función que convierte en estring las llaves del hash y las regresa en un string
 * 
 * @complejidad: O(n) debido a la presencia de un ciclo for dependiente del tamaño del arreglo.
 * 
 * @tparam Key llave para acceder a los datos del hash
 * @tparam Value valores dentro de la tabla
 * @return string datos de las llaves del hash
 */
template <class Key, class Value>
string Hash<Key, Value>::toString() const {
	stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

/**
 * @brief Función que inserta un valor en la tabla y le asigna una llave para su posterior consulta.
 * 
 * @complejidad: O(n) debido a la presencia de un ciclo for dependiente del tamaño del arreglo.
 * 
 * @tparam Key llave para acceder a los datos del hash
 * @tparam Value valores dentro de la tabla
 * @param k llave que se le asignará al valor
 * @param v valor que se le asignará a la llave
 */
template <class Key, class Value>
void Hash<Key, Value>::put(Key k, Value v){
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return;
	}

	start = i = func(k) % size;

	for(int j= 0; j < size; j++){
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
            return;
		}
		i = (start + j*j) % size;
	}
	return;
}

/**
 * @brief función que regresa el valor asociado a una llave
 * 
 * @complejidad: Podría clasificarse como un O(1) debido a que en sí no presenta ningún ciclo, pero como manda a llamar
 * a la función indexOf que presenta una complejidad de O(n) y siendo que se debe tomar en cuenta la complejidad más 
 * grande, se catalogaría como O(n)
 * 
 * @tparam Key llave para acceder al valor del hash
 * @tparam Value valores almacenados en la tabla
 * @param k llave que se usará para calcular la posición del valor
 * @return Value valor que se guardó en la hash table.
 */
template <class Key, class Value>
Value Hash<Key, Value>::get(const Key k){
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
	return "Not found";
}

#endif