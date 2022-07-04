#include "HuffmanNode.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "HuffmanNode.hpp"


#include "IO.hpp"

#define INTERNAL_NODE_VALUE -1
#define FREQUENCY_VALUE -1

class HuffmanDecoding {
    HuffmanNode *root;
    uint8_t *memoryBlock;
    int size;
    uint8_t chunkCount = 0;
    uint8_t* buffer;
    char *fileName;
    
    public:
        HuffmanDecoding(char * filename);
        bool openFile();
        void decode();
        void writeDecodedDataToBuffer(uint8_t data);
        void parseFile();
        void createNodeLineage(uint8_t data, int prefix);
        void createHuffmanTree();
        int readIntegerFromBuffer(int index);
        void createRoot();
};