HuffmanNode* createNode(int data, int frequency, HuffmanNode* left, HuffmanNode* right);

typedef struct HuffmanNode {
    int frequency;
    int data;
    HuffmanNode* left;
    HuffmanNode* right;
} HuffmanNode;

