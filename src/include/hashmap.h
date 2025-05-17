#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <math.h>
#include "vector.h"

using std::cout;
using std::string;

/**
 * @brief Par clave-valor utilizado en la tabla hash.
 * @tparam K Tipo de la clave.
 * @tparam V Tipo del valor.
 */
template<typename K, typename V>
struct Pair{
    K key;    ///< Clave del par.
    V value;  ///< Valor asociado a la clave.
    bool empty; ///< Indica si la celda está vacía.

    /**
     * @brief Constructor por defecto. Marca el par como vacío.
     */
    Pair(){
        key = K();
        value = V();
        empty = true;
    }

    /**
     * @brief Constructor con clave y valor.
     * @param key Clave.
     * @param value Valor.
     */
    Pair(K key, V value){
        this->key = key;
        this->value = value;
        this->empty = false;
    }
    
    /**
     * @brief Operador de comparación de igualdad.
     * @param p Otro par a comparar.
     * @return true si las claves y los valores son iguales.
     */
    bool operator== (Pair<K,V>& p) const{
        return key == p.key && value == p.value;
    }

    /**
     * @brief Operador de comparación de desigualdad.
     * @param p Otro par a comparar.
     * @return true si la clave o el valor es diferente.
     */
    bool operator!= (Pair<K,V>& p){
        return key != p.key || value != p.value;
    }
};

/**
 * @brief Implementación de un HashMap con open addressing y rehashing.
 * @tparam K Tipo de clave.
 * @tparam V Tipo de valor.
 */
template<typename K, typename V>
class HashMap{
public:
    /**
     * @brief Constructor.
     * @param tableSize Tamaño inicial de la tabla.
     * @param loadFactor Factor de carga para redimensionar.
     */
    HashMap(int tableSize = 11, float loadFactor = 0.75f){
        table = Vector<Pair<K,V>>(tableSize);
        this->loadFactor = loadFactor;
        this->size = 0;
    }

    /**
     * @brief Inserta un par clave-valor en el mapa.
     * @param key Clave.
     * @param value Valor.
     * @return true si se inserta exitosamente, false si ya existe ese par.
     */
    bool insert(K key, V value){
        Pair<K,V> p(key, value);
        int hashIndex = hash(key);
        int index;
        int i = 0;
        while(i < table.getCapacity()){
            index = (hashIndex + i * i) % table.getCapacity();
            if(table[index] == p){
                return false;
            }
            if(table[index].empty){
                table[index] = p;
                size++;
                if(size > table.getCapacity() * loadFactor){
                    expand();
                }
                return true;
            }
            i++;
        }
        return false;
    }

    /**
     * @brief Devuelve el número de elementos almacenados.
     * @return Cantidad de elementos.
     */
    int getSize(){
        return size;
    }

    /**
     * @brief Verifica si una clave está presente en el mapa.
     * @param key Clave a buscar.
     * @return true si existe la clave, false si no.
     */
    bool containsKey(K& key){
    int hashIndex = hash(key);
    int index;
    int i = 0;
    do{
        index = (hashIndex + i * i) % table.getCapacity();
        if (table[index].empty) return false;
        if (table[index].key == key && !table[index].empty) return true;
        i++;
    } while(i < table.getCapacity());
    return false;
    }

    /**
     * @brief Elimina una clave y su valor asociado.
     * @param key Clave a eliminar.
     * @return true si la eliminación es exitosa, false si no existe la clave.
     */
    bool remove(K key){
        int hashIndex = hash(key);
        int index;
        int i = 0;
        do{
            index = (hashIndex + i * i) % table.getCapacity();
            if(table[index].empty){
                return false;
            }
            if(table[index].key == key){
                table[index] = Pair<K,V>();
                table[index].empty = true;
                size--;
                return true;
            }
            i++;
        }
        while(i < table.getCapacity());
        return false;
    }

    /**
     * @brief Verifica si el HashMap está vacío.
     * @return true si está vacío, false si no.
     */
    bool isEmpty(){
        return size == 0;
    }

    /**
     * @brief Accede al valor asociado a una clave (operador corchete).
     * @param key Clave.
     * @return Referencia al valor asociado (lo crea si no existe).
     */
    V& operator[](const K& key){
        int hashIndex = hash(key);
        int index = 0;
        int i = 0;
        int capacity = table.getCapacity();
        while (i < capacity) {
            index = (hashIndex + i * i) % capacity;
            if (!table[index].empty && table[index].key == key) {
                return table[index].value;
            }
            if (table[index].empty) {
                break;
            }
            i++;
        }
        table[index].key = key;
        table[index].value = V();
        table[index].empty = false;
        size++;
        if(size > table.getCapacity() * loadFactor){
            expand();
            return (*this)[key];
        }
        return table[index].value;
    }


    /**
     * @brief Imprime el contenido del mapa por consola.
     */
    void print(){
        cout << "---HASHMAP----\n";
        for(int i = 0; i < table.getCapacity(); i++){
            if (!table[i].empty){
                cout << "map[" << table[i].key << "]: " << table[i].value << "\n";
            }
        }
        cout << "--------------\n";
    }

    /**
     * @brief Calcula el hash de una clave.
     * @param key Clave.
     * @return Valor hash.
     */
    int hash(K key){
        string str;
        if constexpr (std::is_same<K,string>::value){
            str = key;
        }
        else if constexpr (std::is_arithmetic<K>::value){
            str = std::to_string(key);
        }
        else{
            str = key.to_string();
        }
        unsigned int hashVal = 0;
        for (char ch : str) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % table.getCapacity();
    }

    /**
     * @brief Iterador de la tabla hash.
     */
    class Iterator {
    private:
        Pair<K,V>* ptr;
        Pair<K,V>* end;
    public:
        /**
         * @brief Constructor del iterador.
         * @param p Puntero inicial.
         * @param e Puntero final.
         */
        Iterator(Pair<K,V>* p, Pair<K,V>*e) : ptr(p), end(e) {}
        
        /**
         * @brief Operador de acceso al elemento.
         * @return Referencia al par actual.
         */
        Pair<K,V>& operator*() const { return *ptr; }

        /**
         * @brief Operador de incremento.
         * @return Referencia al iterador avanzado.
         */
        Iterator& operator++() {
            ++ptr;
            while(ptr->empty and ptr != end){
                ptr++;
            }
            return *this; 
        }

        /**
         * @brief Operador de desigualdad entre iteradores.
         * @param other Otro iterador.
         * @return true si son diferentes.
         */
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    
    /**
     * @brief Devuelve un iterador al principio del mapa.
     */
    Iterator begin() { return Iterator(&table[0], &table[table.getCapacity()]); }
    /**
     * @brief Devuelve un iterador al final del mapa.
     */
    Iterator end()   { return Iterator(&table[table.getCapacity()], &table[table.getCapacity()]); }
private:
    Vector<Pair<K,V>> table; ///< Tabla interna de pares.
    double loadFactor;       ///< Factor de carga para expansión.
    int size;               ///< Número de elementos actuales.

    /**
     * @brief Verifica si un número es primo.
     * @param n Número a verificar.
     * @return true si es primo.
     */
    bool isPrime(int n){
        if(n < 2){
            return false;
        }
        if(n == 2 || n == 3){
            return true;
        }
        if (n % 2 == 0 || n % 3 == 0){
            return false;
        }
        for (int i = 5; i * i <= n; i += 6){
            if (n % i == 0 || n % (i + 2) == 0){
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Busca el siguiente primo mayor o igual que n.
     * @param n Límite inferior.
     * @return Primer número primo mayor o igual que n.
     */
    int nextPrime(int n){
        while(!isPrime(n)){
            n++;
        }
        return n;
    }

    /**
     * @brief Expande la tabla y reubica todos los elementos.
     */
    void expand(){
        Vector<Pair<K,V>> oldTable = table;
        int newCapacity = nextPrime(2 * table.getCapacity());
        table = Vector<Pair<K,V>>(newCapacity);
        size = 0;

        for(int i = 0; i < oldTable.getCapacity(); i++){
            if(!oldTable[i].empty){
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
    }
};
