#include "HuffmanEncoding.hpp"

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
    freqArray = (int*)malloc(sizeof(int)*CHUNK_SIZE);
    int numChunks; //TODO
    for(int i = 0; i<numChunks; i++){
        int chunk; //TODO
        freqArray[chunk]++;
    }
}

void HuffmanEncoding::buildFrequencyQueue(){
    frequencyQueue = new PriorityQueue(CHUNK_SIZE);
    for(int i =0; i<CHUNK_SIZE; i++){
        HuffmanNode* node = createNode(i,freqArray[i], NULL,NULL);
        frequencyQueue->add(node);
    }
}

void buildTree() {
    while (frequencyQueue->getSize() > 1) {
        //extract two nodes
        HuffmanNode* left = frequencyQueue->pop();
        HuffmanNode* right = frequencyQueue->pop();

        //create new internal node
        int internalNodeFrequency = left->frequency + right->frequency;
        HuffmanNode* node = createNode(INTERNAL_NODE_VALUE, internalNodeFrequency, left, right);

        //add to pq
        frequencyQueue->add(node);          
    }
    root = frequencyQueue->pop();
}

void buildCompressedFile(){
    
}
void addNode();  
        
