#include <iostream>
#include "include/priority_queue.h"

using namespace std;

int main() {
    PriorityQueue<int> pq;
   
    pq.enqueue(5);
    pq.enqueue(2);
    pq.enqueue(8);
    pq.enqueue(1);
    pq.enqueue(2);
    
    pq.print();
    pq.peek();
    
    pq.dequeue();
    pq.print();

    pq.dequeue();
    pq.print();
    
    pq.dequeue();
    pq.print();
    return 0;
}
