# airdrop-but-better

8 bit vs 16 bit nodes
    8 bit -> less efficient encode bc higher probability of all possible 8 bits existing
    16 bit -> larger ram needed but smaller file size bc lower probability of all possible 16 bits existing
send tree or map
    tree -> larger file size faster decode. solution: slim down tree by recording pre order. How do we know what is leaf/internal node? -1
    there are only 256 numbers in 8 bit how do you represent -1 ... 255?????
    map -> smaller file size, simpler encode, slower decode (ammortize O(1) worst case O(n)). but don't know implementation of std::map so how to get map memory

bitset copy and paste
big endian vs little endian left shift

