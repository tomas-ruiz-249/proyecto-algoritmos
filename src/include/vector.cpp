#include <string>
#include <iostream>

using namespace std;

template <typename T>
class Vector{
    public:
        Vector(){
            arr = nullptr;
            size = 0;
            capacity = 0;
        }

        int tamaño(){
            return size;
        }

        int capacidad(){
            return capacity;
        }

        void crecer(){
            T* nuevoArr = new T[capacity * 2]();
            for(int i = 0; i < size; i++){
                nuevoArr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevoArr;
            capacity *= 2;
        }

        void encoger(){
            capacity = size;
            T* nuevo_arr = new T[capacity]();
            for(int i = 0; i < capacity; i++){
                nuevo_arr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevo_arr;
        }

        void push(T dato){
            if (capacity == 0){
                arr = new T[1]();
                capacity = 1;
            }
            if(size == capacity){
                crecer();
            }
            arr[size] = dato;
            size++;
        }

        T pop(int indice = -1){
            if(size < 0){
                throw std::out_of_range("pop() no puede ser llamado en vector vacio.");
            }
            if (indice = -1){
                indice = size - 1;
            }
            T dato = arr[indice];
            for(int i = indice; i < capacity; i++){
                arr[i] = arr[i+1];
            }
            size--;
            if(size == capacity/2){
                encoger();
            }
            return dato;
        }
        
        T& operator[](int index){
            return arr[index];
        }

        string str(){
            string str;
            for(int i = 0; i < capacity; i++){
                str += std::to_string(arr[i]);
            }
            return str;
        }

    private:
        T* arr;
        int size;
        int capacity;
};