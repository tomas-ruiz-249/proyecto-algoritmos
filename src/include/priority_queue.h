#include "vector.h"

template<typename T>
class PriorityQueue{
public:
    PriorityQueue();
    void enqueue(T value);
    T dequeue();
    T peek();
private:
    Vector<T> minHeap;
};