#include "min-heap.hpp"
#include <stdlib.h>

class HuffmanEncoding{
    public:
        HuffmanEncoding(char* fileName_);
        void encode();


    private:
        int* freqArray;
        char* fileName;
        void buildFrequencyArray();
        void buildTree();
        void buildFrequencyQueue();
        void addNode();  
         
}