#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "List.h"
#include "Node.h"
#include "ListLinked.h"


template <typename V>
class HashTable: public Dict<V> {

    private:
        // ...
        int n; //Número de elementos almacenados actualmente en la tabla hash.
        int max; //Tamaño de la tabla hash (número total de cubetas).
        ListLinked<TableEntry<V>>* table; //Array de listas enlazadas.

        int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c); // Suma de los valores ASCII de los caracteres
        }
        return sum % max; // Resto de la división entre la suma y el tamaño de la tabla
    }

    public:
        // Constructor
        HashTable(int size) : n(n), max(size), table(new ListLinked<TableEntry<V>>[size]) {};
        //Destructor
        ~HashTable(){
            delete[] table;
        }

        V search (std::string key)override{
            int index = h(key);
            int pos = table[index].search(TableEntry<V>(key));
            return pos;
        };

        void insert (std::string key, V value)override{
            int index = h(key);
            if (table[index].search(TableEntry<V>(key)) != -1) {
                throw std::runtime_error("Key already exists");
            }
            table[index].append(TableEntry<V>(key, value));
            n++;
        };

        V remove (std::string key)override{
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
            out << "HashTable(" << th.n << "/" << th.max << "): {";
            for(int i = 0; i < th.max; i++){
                out << th.table[i];
            }
            out << "}";
            return out;
        }
        V operator[](std::string key){
        try {
            int pos = h(key);
            for (V node : table[pos]) {
                if (node.key == key) {
                    return node.value;
                }
            }
            throw std::runtime_error("Key not found");
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
        }
};

#endif