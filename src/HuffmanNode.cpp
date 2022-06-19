#include <stdlib.h>
#include "HuffmanNode.hpp"

HuffmanNode* createNode(int data, int frequency, HuffmanNode* left, HuffmanNode* right){
    HuffmanNode * node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->data = data;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}