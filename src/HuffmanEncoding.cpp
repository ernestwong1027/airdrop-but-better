#include "HuffmanEncoding.hpp"
#include <arpa/inet.h>
#include <stdio.h>
#include "IO.hpp"
#include <queue>
#include <iostream>
#include<time.h>
#include <time.h>
#include <stdlib.h>

HuffmanEncoding::HuffmanEncoding(char* fileName_){
    srand(time(NULL));
    fileName = fileName_;
}

ExecuteResult HuffmanEncoding::encode(){
    if(!openFile()) return EXECUTE_INVALID_FILE;
    buildFrequencyArray();
    buildFrequencyQueue();
    buildTree();
    buildCompressedFile();
    return EXECUTE_SUCCESS;
}

bool HuffmanEncoding::openFile(){
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) return 0;
    
    fseek(file, 0, SEEK_END);
    size = ftell(file); 
    fseek(file, 0, SEEK_SET);

    buffer = (uint8_t*)malloc(size);
    fread(buffer, 1, size, file);
    
    return 1;

}

void HuffmanEncoding::createFile(void *ptr, size_t size) {
    //create file pointer
    int r = rand();
    char* filename_ = (char *)malloc(20*sizeof(char));
    std::sprintf(filename_,"%d",r);
    FILE* file = fopen(filename_, "wb+"); 
    fwrite(ptr, size, 1, file);    
}

void debugPrint(int x){
    if(x==-1) {
        printf("-1\n");
        return;
    }
    uint8_t byte = (uint8_t) x;
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
    printf("%d\n", byte);
}

void HuffmanEncoding::buildFrequencyArray(){
    freqArray = (int*)malloc(sizeof(int)*CHUNK_SIZE);
    for(int i = 0; i<size; i++){         
        uint8_t chunk = buffer[i];
        freqArray[chunk]++;
    }
}



void HuffmanEncoding::buildFrequencyQueue(){
    frequencyQueue = new PriorityQueue(256);
    for(int i =0; i<256; i++){
        if(freqArray[i]==0)continue;
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
    memoryBlock = (uint8_t*) malloc(128* 1E6);
    currentMemoryBlockPtr = memoryBlock + 16;

    createMap(root, 0);

    int cleverInternalNodePlaceholder = -1;

    for(int j = 0; j<256; ++j) {
        if (decodingMap.find(j)==decodingMap.end()) {
            cleverInternalNodePlaceholder = j;
            break;
        }
    }


    //tree size, num chunks, 
    if(cleverInternalNodePlaceholder!=-1) encodeTreeInorder(root,(uint8_t)cleverInternalNodePlaceholder);
    unsigned int encodedTreeSize = (uint8_t*)currentMemoryBlockPtr - (uint8_t*)memoryBlock - 16;
    memcpy(memoryBlock, &encodedTreeSize, sizeof(unsigned int));
    memcpy(memoryBlock + 4, &cleverInternalNodePlaceholder, sizeof(int))
    encodeTreePreorder(root,(uint8_t)cleverInternalNodePlaceholder);
    int chunkBitCounter = encodeChunks();
    int chunkByteCounter = chunkBitCounter % 8 == 0 ? chunkBitCounter / 8 : chunkBitCounter/ 8  + 1;
    printf("%d",chunkBitCounter);
    int chunkOffset = (chunkBitCounter %8);
    memcpy(memoryBlock+8,&chunkByteCounter,sizeof(int));
    memcpy(memoryBlock+12,&chunkOffset,sizeof(int));
    createFile(memoryBlock,(currentMemoryBlockPtr+4)-memoryBlock);

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

void HuffmanEncoding::encodeTreeInorder(HuffmanNode *node, uint8_t cleverInternalNodePlaceholder) {
    

    if (node == NULL) return;
    encodeTreeInorder(node->left, cleverInternalNodePlaceholder);


    uint8_t data = node->data == INTERNAL_NODE_VALUE ? cleverInternalNodePlaceholder: node->data;
    memcpy(currentMemoryBlockPtr, &data, sizeof(uint8_t));

    ++currentMemoryBlockPtr;

    encodeTreeInorder(node->right, cleverInternalNodePlaceholder);

}

// send clever node

void HuffmanEncoding::encodeTreePreorder(HuffmanNode *node, uint8_t cleverInternalNodePlaceholder) {
    if (node == NULL) return;
    uint8_t data = node->data == INTERNAL_NODE_VALUE ? cleverInternalNodePlaceholder: node->data;
    memcpy(currentMemoryBlockPtr, &data, sizeof(uint8_t));
    ++currentMemoryBlockPtr;
    encodeTreePreorder(node->left, cleverInternalNodePlaceholder);
    encodeTreePreorder(node->right, cleverInternalNodePlaceholder);
}


int HuffmanEncoding::encodeChunks() {
    int counter = 0;
    uint8_t current_byte = 0;
    for(int i = 0; i<size; i++){
        uint8_t chunk = buffer[i];
        uint8_t encodedData = encodingMap[chunk];
        int numZeroes = 0;
        for(; numZeroes<8; numZeroes++){
            if(encodedData >= CHUNK_SIZE/2)break;
            encodedData = encodedData<<1;  
        }
        
        int numDigits = numZeroes == 8 ? 1 : (8-numZeroes);

        encodedData = encodingMap[chunk];
        for(int j = 0; j<numDigits; j++)
        {
            if(encodedData%2==1) current_byte++;
            counter++;
            current_byte = (current_byte << 2);
            encodedData /= 2;
             if(counter % 8 == 0){
                memcpy(currentMemoryBlockPtr, &current_byte, 1);
                currentMemoryBlockPtr++;
            }
        }

    }
    memcpy(currentMemoryBlockPtr, &current_byte, 1);
    currentMemoryBlockPtr++;
    return counter;    

}
