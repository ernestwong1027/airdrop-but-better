#include <stdlib.h>
#include <stdio.h>
#include <bitset>

int main (){
    std::bitset<1000000> *encodedChunks = (std::bitset<1000000>*)malloc(sizeof(std::bitset<1000000>));
    printf("%lu",sizeof(*encodedChunks));

}