
#include "PriorityQueue.hpp"
#include "HuffmanNode.hpp"

PriorityQueue::PriorityQueue(int capacity) {
    heap = new HuffmanNode[capacity];
    capacity = 0;
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete heap;
}

void PriorityQueue::add(HuffmanNode *node) {
    if (size == capacity) return;
    heap[size] = *node;
    size += 1;
    return bottom_up(size);
}

HuffmanNode* PriorityQueue::pop() {
    swap(&heap[0].frequency, &heap[size - 1].frequency);
    size -= 1;
    top_down(0);
    return &heap[0];
}

int PriorityQueue::getSize(){
    return size;
}

void PriorityQueue::swap(int *a, int *b) {
    int temp = *a;
    *a = *b;  
    *b = temp;
}

void PriorityQueue::bottom_up(int child) {
    int parent = (child - 1) / 2;
    if (parent < 0 || heap[child].frequency <= heap[parent].frequency) return;
    swap(&heap[child].frequency, &heap[parent].frequency);
    return bottom_up(parent);
}

void PriorityQueue::top_down(int parent) {
    int left_child = parent * 2 + 1;
    int right_child = parent * 2 + 2;

    if (left_child > size) return;

    if (left_child < size && right_child >= size && heap[parent].frequency >= heap[left_child].frequency) {
        swap(&heap[parent].frequency, &heap[left_child].frequency);
        return top_down(left_child);
    } 

    if (heap[parent].frequency <= heap[left_child].frequency && heap[parent].frequency <= heap[right_child].frequency) return;

    if (heap[left_child].frequency >= heap[right_child].frequency) {
        swap(&heap[right_child].frequency, &heap[parent].frequency);
        return top_down(right_child);
    }

    swap(&heap[left_child].frequency, &heap[parent].frequency);
    return top_down(left_child);
}


    




