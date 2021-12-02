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

template <class Key, class Value>
bool Hash<Key, Value>::full() const {
	return (count > size);
}

template <class Key, class Value>
void Hash<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}

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