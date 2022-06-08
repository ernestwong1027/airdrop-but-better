
#include "min-heap.hpp"
#include "HuffmanNode.hpp"

PriorityQueue::PriorityQueue(int size) {
    capacity = 0;
    heap = new HuffmanNode[size];
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete heap;
}

void PriorityQueue::swap(int *a, int *b) {
    int temp = *a;
    *a = *b;  
    *b = temp;
}

void PriorityQueue::bottom_up(int child) {
    int parent = (child - 1) / 2;

    if (parent < 0 || heap[child].frequency <= heap[parent].frequency) {
        return;
    }

    swap(&heap[child].frequency, &heap[parent].frequency);

    return bottom_up(parent);
}

void PriorityQueue::top_down(int parent) {
    int left_child = parent * 2 + 1;
    int right_child = parent * 2 + 2;


    if (left_child > capacity) {
        return;
    }
    
    
    if (left_child < capacity && right_child >= capacity && heap[parent].frequency >= heap[left_child].frequency) {
        swap(&heap[parent].frequency, &heap[left_child].frequency);
        return top_down(left_child);
    } 

    if (heap[parent].frequency <= heap[left_child].frequency && heap[parent].frequency <= heap[right_child].frequency) {
        return;
    }

    if (heap[left_child].frequency >= heap[right_child].frequency) {
        swap(&heap[right_child].frequency, &heap[parent].frequency);
        return top_down(right_child);
    }

    swap(&heap[left_child].frequency, &heap[parent].frequency);
    return top_down(left_child);
}

void PriorityQueue::add(HuffmanNode *node) {

    if (size >= capacity) {
        return;
    }

    size += 1;
    heap[size] = *node;
    return bottom_up(size);
}

HuffmanNode* PriorityQueue::pop() {

    swap(&heap[0].frequency, &heap[size].frequency);
    
    size -= 1;

    top_down(0);

    return &heap[0];
}
    




