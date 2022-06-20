#include "PriorityQueue.hpp"
#include "HuffmanNode.hpp"
#include <stdlib.h>
#include <bitset>
#include <iostream>
#include <map>
#include "IO.hpp"

#define CHUNK_SIZE 256
#define INTERNAL_NODE_VALUE -1

class HuffmanEncoding {
      
    public:
        HuffmanEncoding(char* fileName_);

        int* freqArray;
        char* fileName;
        long size;
        uint8_t * buffer;
        PriorityQueue* frequencyQueue;
        HuffmanNode* root;
        std::map<int,uint8_t> encodingMap;
        std::map<int,int> decodingMap;
        uint8_t* memoryBlock;
        uint8_t* currentMemoryBlockPtr;
        bool openFile();
        void buildFrequencyArray();
        void buildTree();
        void buildFrequencyQueue();
        int encodeChunks();   
        void buildCompressedFile();
        void createMap(HuffmanNode *node, int prefix);
        int mapToArray();
        // void encodeTreeInorder(HuffmanNode *node, uint8_t cleverInternalNodePlaceholder);
        // void encodeTreePreorder(HuffmanNode *node, uint8_t cleverInternalNodePlaceholder);
        ExecuteResult encode();
};