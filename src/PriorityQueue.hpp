#include "HuffmanNode.hpp"
#include <stdlib.h>
#include <algorithm>

class PriorityQueue {
    
    
    public:
        PriorityQueue(int capacity);
        ~PriorityQueue();
        void add(HuffmanNode *node);
        HuffmanNode* pop();
        int getSize();

    private:
        HuffmanNode **heap;
        void swap(int a, int b);
        int size;
        void bottom_up(int child);
        void top_down(int parent);
        
};