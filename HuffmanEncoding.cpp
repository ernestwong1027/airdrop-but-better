#include "HuffmanEncoding.hpp"
#include <bitset>
#include <arpa/inet.h>

HuffmanEncoding::HuffmanEncoding(char* fileName_){
    fileName = fileName_;
}

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

void HuffmanEncoding::buildTree() {
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

void HuffmanEncoding::buildCompressedFile(){
    //malloc raw memory
    memoryBlock = (int*) malloc(128* 1E6);
    currentMemoryBlockPtr = memoryBlock + 8;

    createMap(root, 0);

    int cleverInternalNodePlaceholder = -1;
    for(int j = 0; j<256; ++j) {
        if (decodingMap.find(j)==decodingMap.end()) {
            cleverInternalNodePlaceholder = j;
            break;
        }
    }

    if(cleverInternalNodePlaceholder!=-1) encodeTree(root,(uint8_t)cleverInternalNodePlaceholder);
    unsigned int encodedTreeSize = (int*)currentMemoryBlockPtr - (int*)memoryBlock - 8;
    memcpy(memoryBlock, &encodedTreeSize, 4);

    int chunkBitCounter = encodeChunks();    
    int chunkByteCounter = chunkBitCounter % 8 == 0 ? chunkBitCounter / 8 : chunkBitCounter/ 8  + 1;
    int chunkOffset = 8-(chunkBitCounter %8);
    memcpy(memoryBlock+4,&chunkByteCounter,sizeof(int));
    memcpy(currentMemoryBlockPtr,&chunkOffset,sizeof(int));
}

void HuffmanEncoding::createMap(HuffmanNode* node, int prefix) {

    if (node->left) createMap(node->left, prefix<<1);    
    if (node->right) createMap(node->right, (prefix<<1)+1); 
    
    //leaf node
    if (node->left == NULL && node->right == NULL) {
        encodingMap[node->data] = prefix;
        decodingMap[prefix] = node->data;
       return;
    }
}


void HuffmanEncoding::encodeTree(HuffmanNode *node, uint8_t cleverInternalNodePlaceholder) {
    if (node == NULL) return;

    encodeTree(node->left, cleverInternalNodePlaceholder);

    uint8_t data = node->data == INTERNAL_NODE_VALUE ? cleverInternalNodePlaceholder: node->data;
    memcpy(currentMemoryBlockPtr, &data, sizeof(uint8_t));
    ++currentMemoryBlockPtr;

    encodeTree(node->right, cleverInternalNodePlaceholder);
}


int HuffmanEncoding::encodeChunks() {
    std::bitset<100000000> encodedChunks;
    int numChunks; //TODO

    int counter = 0;

    for(int i = 0; i<numChunks; i++){
        int chunk; //TODO
        uint8_t encodedData = encodingMap[chunk];
        int numZeroes = 0;
        
        for(; numZeroes<CHUNK_SIZE; numZeroes++){
            if(encodedData >= CHUNK_SIZE/2)break;
            encodedData = encodedData<<1;  
        }
        
        int numDigits = numZeroes == 8 ? 1 :(8-numZeroes);
        counter += numDigits;
        encodedChunks = encodedChunks<<numDigits;
        encodedData = encodingMap[chunk];
        encodedChunks |= encodedData;
    }

    int bytes_to_copy = counter % 8 == 0 ? counter / 8 : counter/ 8  + 1;    
    memcpy(currentMemoryBlockPtr, (&encodedChunks)+125000-bytes_to_copy, bytes_to_copy);
    currentMemoryBlockPtr += bytes_to_copy;

    return counter;    
}
