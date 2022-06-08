#include "PriorityQueue.hpp"
#include "HuffmanNode.hpp"
#include <stdlib.h>
#include <map>

#define CHUNK_SIZE 256
#define INTERNAL_NODE_VALUE -1

class HuffmanEncoding {
    int* freqArray;
    char* fileName;
    PriorityQueue* frequencyQueue;
    HuffmanNode* root;
    std::map<int,uint8_t> encodingMap;
    std::map<int,int> decodingMap;
    int* memoryBlock;
    int* currentMemoryBlockPtr;
    void buildFrequencyArray();
    void buildTree();
    void buildFrequencyQueue();
    int encodeChunks();   
    void buildCompressedFile();
    void createMap(HuffmanNode *node, int prefix);
    void encodeTree(HuffmanNode *node, uint8_t weCleverNode);

    public:
        HuffmanEncoding(char* fileName_);
        void encode();

              
};