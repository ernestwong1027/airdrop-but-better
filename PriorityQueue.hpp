#include "HuffmanNode.hpp"


class PriorityQueue {
    
    HuffmanNode *heap;
    int size;
    int capacity;

    public:
        PriorityQueue(int size);

        ~PriorityQueue();

        void swap(int *a, int *b);

        void bottom_up(int child);

        void top_down(int parent);

        void add(HuffmanNode *node);

        HuffmanNode* pop();
};