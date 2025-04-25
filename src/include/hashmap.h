#include <iostream>
#include <string>
#include <type_traits>
#include <math.h>
#include "vector.h"

using std::cout;
using std::string;

template<typename K, typename V>
struct Pair{
    K key;
    V value;
    bool empty;

    Pair(){
        key = K();
        value = V();
        empty = true;
    }

    Pair(K key, V value){
        this->key = key;
        this->value = value;
        this->empty = false;
    }
    
    bool operator== (Pair<K,V>& p){
        return key == p.key and value == p.value;
    }
};

template<typename K, typename V>
class HashMap{
public:
    HashMap(int tableSize = 11, float loadFactor = 0.75f){
        table = Vector<Pair<K,V>>(tableSize);
        this->loadFactor = loadFactor;
        this->size = 0;
    }

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

    void print(){
        cout << "---HASHMAP----\n";
        for(int i = 0; i < table.getCapacity(); i++){
            if (table[i].empty){
                cout << i << ": ";
                cout << "(empty)\n";
            }
            else{
                cout << i << ": ";
                cout << "( " << table[i].key << ", " << table[i].value << " )\n";
            }
        }
        cout << "--------------\n";
    }

    int hash(K key){
        string str;
        if constexpr (std::is_same<K,string>::value){
            str = key;
        }
        else if constexpr (std::is_arithmetic<K>::value){
            str = std::to_string(key);
        }
        else{
            str = key.str();
        }
        unsigned int hashVal = 0;
        for (char ch : str) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % table.getCapacity();
    }
private:
    Vector<Pair<K,V>> table;
    double loadFactor;
    int size;

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

    int nextPrime(int n){
        while(!isPrime(n)){
            n++;
        }
        return n;
    }

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