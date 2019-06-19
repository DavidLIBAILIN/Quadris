#include <cstdlib>
#include <fstream>
#include "level3.h"

using namespace std;

Level3::Level3(int seed, char nextBlock) : Level{seed, nextBlock}, random{true} {
    vector<char> blocks = {'I', 'J', 'L', 'O', 'S', 'S', 'Z', 'Z', 'T'};
    blockTypes = blocks;
}


char Level3::getNext() {
    if (!random) {
        if (file_pos >= block_order.size()) file_pos = 0;
        char type = block_order.at(file_pos);
        ++file_pos;
        nextBlock = type;
    }
    else {
        int index = rand() % (blockTypes.size());
        nextBlock = blockTypes.at(index);;
    }
    return nextBlock;
}


Block *Level3::createBlock(Grid *g) {
    char tmp = nextBlock;
    nextBlock = getNext();
    return charToBlock(3, tmp, g);
}

void Level3::setRandom(bool input, string file) {
    random = input;
    if (!random) setFile(file);
}

void Level3::setFile(string file) {
    ifstream input(file);
    char s;
    while (input >> s) {
        block_order.emplace_back(s);
    }

    file_pos = 0;
}

Level3::~Level3() {}
