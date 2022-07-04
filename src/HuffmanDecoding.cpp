
#include "HuffmanDecoding.hpp"
#include <iostream>

void dfs2(HuffmanNode *node){
    printf("%d\n", node->data);
    if(node->left)dfs2(node->left);
    if(node->right)dfs2(node->right);
}

HuffmanDecoding::HuffmanDecoding(char* fileName_){    
    srand(time(NULL));
    fileName = fileName_;
    memoryBlock = (uint8_t*) malloc(128* 1E6);
}

bool HuffmanDecoding::openFile(){
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) return 0;
    
    fseek(file, 0, SEEK_END);
    size = ftell(file); 
    fseek(file, 0, SEEK_SET);

    buffer = (uint8_t*)malloc(size);
    fread(buffer, 1, size, file);
    
    return 1;

}
void HuffmanDecoding::decode() {
    //decode the tree

    openFile();
    createHuffmanTree();
    dfs2(root);
    parseFile();
    createFile(memoryBlock, chunkCount);

}


void HuffmanDecoding::parseFile() {
    int numNodes = readIntegerFromBuffer(0);
    int numChunks = readIntegerFromBuffer(4);
    int chunkBitOffset = readIntegerFromBuffer(8);
    uint8_t *pointer = buffer + 12 + numNodes * 5;
    HuffmanNode *currentNode = root;

    for(int i =0; i < numChunks; ++i) {
        int j = i == numChunks-1?chunkBitOffset-1:7;
        for( ;j>=0; j--){           

            if (*(pointer + i)/(1<<j)%2==1){
                currentNode = currentNode->right;
                printf("a\n");
            } 
            else {currentNode = currentNode->left; printf("b\n"); }        
            
            if(currentNode->data!=-1){
                printf("%d %d %d\n",i,j,currentNode->data);
                writeDecodedDataToBuffer(currentNode->data);
                currentNode = root;
            }
        }
    }
}

void HuffmanDecoding::writeDecodedDataToBuffer(uint8_t data){
    // std::cout << data << std::endl;
    memcpy(memoryBlock + chunkCount, &data, 1);
    chunkCount += 1;
}

void HuffmanDecoding::createHuffmanTree() {
    int numNodes = readIntegerFromBuffer(0);
    createRoot();
    for(int i = 0; i<numNodes; i++){
        uint8_t data = buffer[12+i*5];
        int prefix = readIntegerFromBuffer(12+i*5+1);
        createNodeLineage(data, prefix);
    }
}

void HuffmanDecoding::createRoot() {
    root = createNode(-1, -1, NULL, NULL);
}

void HuffmanDecoding::createNodeLineage(uint8_t data, int prefix){
    HuffmanNode *currentNode = root;
    if(prefix==0){
        root->left = createNode(data,-1,NULL,NULL);
        return;
    }
    bool encounteredStart = false;
    for(int i = 31; i >= 0; i--){
        
        if(encounteredStart){
            if((prefix/(1<<i))%2==1){
                if(currentNode->right == NULL)currentNode->right = createNode(-1,-1,NULL,NULL);
                currentNode = currentNode->right;
                continue;
            } 
            if(currentNode->left == NULL)currentNode->left = createNode(-1,-1,NULL,NULL);
            currentNode = currentNode->left;
            continue;
        }

        if(prefix/(1<<i)%2==1){
            encounteredStart = true;
            i++;
        }
        
    }
    currentNode->data = data;
}

int HuffmanDecoding::readIntegerFromBuffer(int index){
    int ret;
    memcpy(&ret, buffer + index, 4);
    return ret;
}