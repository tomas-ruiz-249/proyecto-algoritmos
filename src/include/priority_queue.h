template<typename T>
class PriorityQueue{
public:
    PriorityQueue();
    void enqueue(T value);
    T dequeue();
    T peek();
private:
    T* minHeap;
};