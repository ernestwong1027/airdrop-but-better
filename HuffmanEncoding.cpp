#include "HuffmanEncoding.hpp"
#include "PriorityQueue.hpp"

HuffmanEncoding::HuffmanEncoding(char* fileName_){
    fileName = fileName_;
    //Create file instance variable
}
//8 bit vs 32 bit nodes
//send tree or map
void HuffmanEncoding::encode(){
    buildFrequencyArray();
    buildFrequencyQueue();
    buildTree();
    buildCompressedFile();
}

void HuffmanEncoding::buildFrequencyArray(){
    freqArray = (int*)malloc(sizeof(int)*256);
    int numChunks; //TODO
    for(int i = 0; i<numChunks; i++){
        int chunk; //TODO
        freqArray[chunk]++;
    }
}

void HuffmanEncoding::buildFrequencyQueue(){
    PriorityQueue* frequencyQueue = new PriorityQueue();
}

void buildTree() {

}

void buildCompressedFile();
void addNode();  
        
