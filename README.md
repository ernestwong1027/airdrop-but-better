# Airdrop But Better
Cross-platform wireless file sharing interface made from scratch using C++, Huffman encoding and data compression. Made for fun because we were interested in learning more about compression and add our own twist to it! The tool can compress any type of file in a lossless manner.

## Features left to be implemented
- CLI
- Docker file

## A Rough decisioning Log
### 8 bit vs 16 bit nodes
    8 bit -> less efficient encode bc higher probability of all possible 8 bits existing
    16 bit -> larger ram needed but smaller file size bc lower probability of all possible 16 bits existing
### send tree or map
    tree -> larger file size faster decode. solution: slim down tree by recording pre order. How do we know what is leaf/internal node? -1
    there are only 256 numbers in 8 bit how do you represent -1 ... 255? Solution? We loop through numbers from 0-255 and see which numer isn't taken and use that to represent -1. If all 256 numbers are taken (very unlikely) the compression won't be that effective anyways. So, just don't compress if it's all taken.
    map -> smaller file size, simpler encode, slower decode (ammortize O(1) worst case O(n)). but don't know implementation of std::map so how to get map memory

### big endian vs little endian left shift

