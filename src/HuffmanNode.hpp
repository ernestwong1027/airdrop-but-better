#ifndef HUFFMAN_NODE_HEADER
#define HUFFMAN_NODE_HEADER

typedef struct HuffmanNode {
    int frequency;
    int data;
    HuffmanNode* left;
    HuffmanNode* right;
} HuffmanNode;

HuffmanNode* createNode(int data, int frequency, HuffmanNode* left, HuffmanNode* right);
#endif

