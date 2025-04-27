#include "vector.h"
#include <iostream>  // Para std::cout

template<typename T>
class PriorityQueue {
public:
    PriorityQueue() {

    };

    void enqueue(T value) {
        minHeap.push(value);
        heapifyUp(minHeap.getSize() - 1);
    }

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

    T peek() {
        if (minHeap.getSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return minHeap[0];
    }

    bool isHeapEmpty() {
        return minHeap.getSize() == 0;
    }

    void print() {
        std::cout << "Heap: [";
        for (size_t i = 0; i < minHeap.getSize(); i++) {
            std::cout << minHeap[i] << " ";
        }
        std::cout <<"]"<< std::endl;
    }

private:
    Vector<T> minHeap;

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