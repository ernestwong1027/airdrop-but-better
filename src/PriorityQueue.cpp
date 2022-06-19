#include "PriorityQueue.hpp"

PriorityQueue::PriorityQueue(int capacity) {
    heap = (HuffmanNode **)malloc((capacity+1) * 4);
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    free(heap);
}

void PriorityQueue::add(HuffmanNode *node) {
    size++;
    heap[size] = node;   
    int index = size;
    int parent = size/2;
    while(index > 1 && heap[index]->frequency<heap[parent]->frequency){
        swap(index,parent);
        index = parent;
        parent = index/2;
    }
}

HuffmanNode* PriorityQueue::pop() {
    if(size==0)return NULL;
    HuffmanNode *removed = heap[1];
    heap[1] = heap[size];
    size--;
    int index = 1;
    while(index <= size/2)
    {
        int left_child = index * 2;
        int right_child = (index * 2 )+ 1;
        if(heap[index]->frequency <= heap[left_child]->frequency && heap[index]->frequency <= heap[right_child]->frequency) break;      
        if(heap[left_child]->frequency < heap[right_child]->frequency)
        {
                swap(index, left_child);
                index = left_child;
        }
        else
        {
                swap(index,right_child);
                index = right_child;
        }
    }  
    return removed;
}

void PriorityQueue::swap(int a,int b){
    HuffmanNode *tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
}

int PriorityQueue::getSize(){
    return size;
}




