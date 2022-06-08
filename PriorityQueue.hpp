#include "HuffmanNode.hpp"


class PriorityQueue {
    
    
    public:
        PriorityQueue(int capacity);
        ~PriorityQueue();

        void add(HuffmanNode *node);
        HuffmanNode* pop();
        int getSize();

    private:
        HuffmanNode *heap;
        int size;
        int capacity;
        void swap(int *a, int *b);
        void bottom_up(int child);
        void top_down(int parent);
        
};