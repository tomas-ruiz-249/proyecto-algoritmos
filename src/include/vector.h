#pragma once
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Clase plantilla que implementa un vector dinámico similar a std::vector.
 * @tparam T Tipo de los elementos almacenados.
 */
template <typename T>
class Vector{
    public:
        /**
         * @brief Constructor por defecto. Crea un vector vacío.
         */
        Vector(){
            arr = nullptr;
            size = 0;
            capacity = 0;
        }

        /**
         * @brief Constructor que inicializa el vector con una capacidad específica.
         * @param capacity Capacidad inicial del vector.
         */
        Vector(int capacity){
            arr = new T[capacity]();
            this->capacity = capacity;
            size = 0;
        }

        /**
         * @brief Retorna el número de elementos actuales en el vector.
         * @return Número de elementos.
         */
        int getSize() {
            return size;
        }

        /**
         * @brief Retorna la capacidad actual del vector.
         * @return Capacidad máxima del vector.
         */
        int getCapacity(){
            return capacity;
        }

        /**
         * @brief Duplica la capacidad del vector cuando está lleno.
         */
        void crecer(){
            T* nuevoArr = new T[capacity * 2]();
            for(int i = 0; i < size; i++){
                nuevoArr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevoArr;
            capacity *= 2;
        }

        /**
         * @brief Reduce la capacidad del vector al tamaño actual.
         */
        void encoger(){
            capacity = size;
            T* nuevo_arr = new T[capacity]();
            for(int i = 0; i < capacity; i++){
                nuevo_arr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevo_arr;
        }

        /**
         * @brief Agrega un elemento al final del vector.
         * @param dato Elemento a agregar.
         */
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

        /**
         * @brief Elimina y retorna el elemento en la posición indicada o el último si no se especifica.
         * @param indice Índice del elemento a eliminar (por defecto -1, elimina el último).
         * @return Elemento eliminado.
         * @throws std::out_of_range si el vector está vacío o el índice es inválido.
         */
        T pop(int indice = -1){
            if(size <= 0){
                throw std::out_of_range("pop() no puede ser llamado en vector vacio.");
            }
            if (indice == -1){
                indice = size - 1;
            }
            T dato = arr[indice];
            for(int i = indice; i < capacity-1; i++){
                arr[i] = arr[i+1];
            }
            size--;
            if(size == capacity/2){
                encoger();
            }
            return dato;
        }

        /**
         * @brief Retorna una referencia al elemento en la posición indicada.
         * @param index Índice del elemento.
         * @return Referencia al elemento.
         * @throws std::out_of_range si el índice está fuera de rango.
         */
        T& at(int index){
            if(index >= size)
                throw std::out_of_range("Indice fuera del rango.");
            return arr[index];
        }
        
        /**
         * @brief Operador de acceso por índice.
         * @param index Índice del elemento.
         * @return Referencia al elemento.
         */
        T& operator[](int index) {
            return arr[index];
        }

        /**
         * @brief Convierte el contenido del vector a una cadena.
         * @return Representación en cadena de los elementos.
         */
        string to_string(){
            string str;
            for(int i = 0; i < capacity; i++){
                str += std::to_string(arr[i]);
            }
            return str;
        }

        /**
         * @brief Verifica si un elemento existe en el vector.
         * @param value Elemento a buscar.
         * @return true si el elemento existe, false en caso contrario.
         */
        bool contains(T value){
            for(int i = 0; i < size; i++){
                if (arr[i] == value){
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Iterador para recorrer el vector.
         */
        class Iterator {
        private:
            T* ptr;
        public:
            /**
             * @brief Constructor del iterador.
             * @param p Puntero al primer elemento.
             */
            Iterator(T* p) : ptr(p) {}
            
            /**
             * @brief Operador de desreferenciación.
             * @return Referencia al elemento actual.
             */
            T& operator*() const { return *ptr; }

            /**
             * @brief Operador de incremento.
             * @return Referencia al iterador incrementado.
             */
            Iterator& operator++() { ++ptr; return *this; }

            /**
             * @brief Operador de comparación de desigualdad.
             * @param other Otro iterador.
             * @return true si son distintos, false en caso contrario.
             */
            bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        };
        
        /**
         * @brief Retorna un iterador al inicio del vector.
         * @return Iterador al primer elemento.
         */
        Iterator begin() { return Iterator(arr); }
        
        /**
         * @brief Retorna un iterador al final del vector.
         * @return Iterador al elemento después del último.
         */
        Iterator end()   { return Iterator(arr + size); }
        
    private:
        /**
         * @brief Puntero al arreglo dinámico que almacena los elementos.
         */
        T* arr;
        /**
         * @brief Número de elementos actuales en el vector.
         */
        int size;
        /**
         * @brief Capacidad máxima del vector.
         */
        int capacity;
};
