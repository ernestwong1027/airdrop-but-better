#include "PriorityQueue.hpp"
#include "HuffmanNode.hpp"
#include <stdlib.h>

#define CHUNK_SIZE 256
#define INTERNAL_NODE_VALUE -1

class HuffmanEncoding {
    int* freqArray;
    char* fileName;
    PriorityQueue* frequencyQueue;
    HuffmanNode* root;
    void buildFrequencyArray();
    void buildTree();
    void buildFrequencyQueue();
    void addNode();   

    public:
        HuffmanEncoding(char* fileName_);
        void encode();

              
};