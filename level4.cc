#include <cstdlib>
#include <fstream>
#include "level4.h"

using namespace std;

Level4::Level4(int seed, char nextBlock) : Level{seed, nextBlock}, random{true} {
    vector<char> blocks {'I', 'J', 'L', 'O', 'S', 'S', 'Z', 'Z', 'T'};
    blockTypes = blocks;

}


char Level4::getNext() {
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


Block *Level4::createBlock(Grid *g) {
    char tmp = nextBlock;
    nextBlock = getNext();
    return charToBlock(4, tmp, g);
}

void Level4::setRandom(bool input, string file) {
    random = input;
    if (!random) setFile(file);
}

void Level4::setFile(string file) {
    ifstream input(file);
    char s;
    while (input >> s) {
        block_order.emplace_back(s);
    }

    file_pos = 0;
}


Level4::~Level4() {}
