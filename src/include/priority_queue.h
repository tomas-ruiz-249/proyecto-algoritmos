#pragma once
#include "vector.h"
#include <iostream>  // Para std::cout

/**
 * @brief Implementa una cola de prioridad (min heap) usando un vector dinámico.
 * 
 * @tparam T Tipo de los elementos almacenados en la cola de prioridad. Debe soportar comparación con '<'.
 */
template<typename T>
class PriorityQueue {
public:
    /**
     * @brief Inserta un nuevo elemento en la cola de prioridad.
     * 
     * @param value Valor a insertar.
     */
    void enqueue(T value) {
        minHeap.push(value);
        heapifyUp(minHeap.getSize() - 1);
    }

    /**
     * @brief Elimina y retorna el elemento de mayor prioridad (menor valor).
     * 
     * @return T El elemento de mayor prioridad.
     * @throws std::out_of_range si la cola está vacía.
     */
    T dequeue() {
        if (minHeap.getSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        T minValue = minHeap[0];
        minHeap[0] = minHeap[minHeap.getSize() - 1];
        minHeap.pop();

        if (minHeap.getSize() > 0) {
            heapifyDown(0);
        }
        return minValue;
    }

    /**
     * @brief Consulta el elemento de mayor prioridad sin eliminarlo.
     * 
     * @return T El elemento de mayor prioridad.
     * @throws std::out_of_range si la cola está vacía.
     */
    T peek() {
        if (minHeap.getSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return minHeap[0];
    }

    /**
     * @brief Verifica si la cola de prioridad está vacía.
     * 
     * @return true si está vacía, false en caso contrario.
     */
    bool isEmpty() {
        return minHeap.getSize() == 0;
    }

    /**
     * @brief Imprime todos los elementos de la cola de prioridad (para depuración).
     */
    void print() {
        std::cout << "Priority Queue: [";
        for (size_t i = 0; i < minHeap.getSize(); i++) {
            std::cout << minHeap[i] << " ";
        }
        std::cout <<"]"<< std::endl;
    }

private:
    /**
     * @brief Vector que almacena los elementos del heap.
     */
    Vector<T> minHeap;

    /**
     * @brief Restablece la propiedad de heap desde el índice hacia arriba.
     * 
     * @param index Índice desde donde empezar la subida.
     */
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (minHeap[index] < minHeap[parent]) {
                swap(minHeap[index], minHeap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    /**
     * @brief Restablece la propiedad de heap desde el índice hacia abajo.
     * 
     * @param index Índice desde donde empezar la bajada.
     */
    void heapifyDown(int index) {
        int left, right, smallest;
        int size = minHeap.getSize();
        
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;
            
            if (left < size && minHeap[left] < minHeap[smallest]) {
                smallest = left;
            }
            
            if (right < size && minHeap[right] < minHeap[smallest]) {
                smallest = right;
            }
            
            if (smallest != index) {
                swap(minHeap[index], minHeap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
};
