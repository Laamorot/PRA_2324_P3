#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <iostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        // ...
        int n; //Número de elementos almacenados actualmente en la tabla hash.
        int max; //Tamaño de la tabla hash (número total de cubetas).
        ListLinked<TableEntry<V> > *table; //Array de listas enlazadas.

        int h(const std::string &key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c); // Suma de los valores ASCII de los caracteres
        }
        return sum % max; // Resto de la división entre la suma y el tamaño de la tabla, corresponde a la posicion de la clave en la tabla hash 
    } 

    public:
        // Constructor
        HashTable(int size) : n(0), max(size) {
		this->table = new ListLinked<TableEntry<V> >[max];
	};
        //Destructor
        ~HashTable(){
            delete[] table;
        }

        void insert (const std::string &key, V value)override{
            int index = h(key);
            if (table[index].search(TableEntry<V>(key)) != -1) {
                throw std::runtime_error("Key already exists");
            }
            table[index].append(TableEntry<V>(key, value));
            n++;
        };

        V search (const std::string &key)override{
            int index = h(key);
            int pos = table[index].search(TableEntry<V>(key));
	    if (pos == -1) {
	    	throw std::runtime_error("Key does not exist.");
	    }
            return table[index].get(pos).value;
        };

        

        V remove (const std::string &key)override{
            int index = h(key);
            int pos = table[index].search(TableEntry<V>(key));
            if (pos == -1) {
                throw std::runtime_error("Key not found");
            }
            V value = table[index].remove(pos).value;
            n--;
            return value;
        };

        int entries ()override{
            return n;
        };
        
        //Devuelve la capacidad de la tabla hash
        int capacity(){
            return max;
        }
        //Sobrecarga del operador << para imprimir la tabla hash
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            for(int i = 0; i < th.max; i++){
                out << i << ": " << th.table[i] << std::endl;
        	}
            return out;
        }
        V operator[](const std::string &key) {
		int index = h(key);
		int idx = table[index].search(TableEntry<V>(key));
		if (idx == -1) {
        		throw std::runtime_error("Key not found");
		}
		return table[index].get(idx).value;
	}
};

#endif
