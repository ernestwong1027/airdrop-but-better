#include "HuffmanEncoding.hpp"
#include <arpa/inet.h>
#include <stdio.h>
#include "IO.hpp"
#include <queue>
#include <iostream>
#include<time.h>
#include <stdlib.h>

HuffmanEncoding::HuffmanEncoding(char* fileName_){
    fileName = fileName_;
}
void dfs(HuffmanNode *node){
    printf("%d\n", node->data);
    if(node->left)dfs(node->left);
    if(node->right)dfs(node->right);
}
ExecuteResult HuffmanEncoding::encode(){
    if(!openFile()) return EXECUTE_INVALID_FILE;
    buildFrequencyArray();
    buildFrequencyQueue();
    buildTree();
    buildCompressedFile();
    dfs(root);
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
    currentMemoryBlockPtr = memoryBlock + 12;

    createMap(root, 0);
    int numNodes = mapToArray();
    memcpy(memoryBlock, &numNodes, sizeof(int));

    int chunkBitCounter = encodeChunks();
    int chunkByteCounter = chunkBitCounter % 8 == 0 ? chunkBitCounter / 8 : chunkBitCounter/ 8  + 1;

    int chunkOffset = (chunkBitCounter %8) == 0?8:(chunkBitCounter %8);
    memcpy(memoryBlock+4,&chunkByteCounter,sizeof(int));
    memcpy(memoryBlock+8,&chunkOffset,sizeof(int));
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

int HuffmanEncoding::mapToArray() {
    int counter = 0;
    for (auto const& [key, val] : encodingMap) {
        memcpy(currentMemoryBlockPtr, &key, 1);
        currentMemoryBlockPtr++;
        memcpy(currentMemoryBlockPtr, &val, 4);
        currentMemoryBlockPtr += 4;
        counter += 1;
    }
    printf("%d",counter);
    return counter;
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
       
        for(int j = numDigits-1; j>=0; j--) {
            if((encodedData/(1<<j))%2==1){
            printf("%d %d %d\n", numDigits, chunk, encodedData);
            current_byte++;
            } 
            else{
                 printf("%d %d %db\n", numDigits, chunk, encodedData);
            }


            
            counter++;
             if(counter % 8 == 0){
                printf("%dd\n",current_byte);
                memcpy(currentMemoryBlockPtr, &current_byte, 1);
                currentMemoryBlockPtr++;
                current_byte = 0;
            }
            current_byte = (current_byte << 1);
            printf("%dc\n",current_byte);
        }

    }
    current_byte = current_byte >>1;
    memcpy(currentMemoryBlockPtr, &current_byte, 1);
    currentMemoryBlockPtr++;
    return counter;    

}
