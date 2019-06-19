#include <fstream>
#include "level0.h"


using namespace std;

Level0::Level0(string file, char nextBlock) : Level{0, nextBlock}, file_pos{0} {
    // store all blocks in vector so we dont have to keep open/closing file
    ifstream input(file);
    char s;
    while (input >> s) {
        block_order.emplace_back(s);
    }
}

char Level0::getNext() {
    // no more blocks, restart from first block
    if (file_pos >= block_order.size()) file_pos = 0;
    char type = block_order.at(file_pos);
    ++file_pos;
    nextBlock = type;
    return nextBlock;
}


Block* Level0::createBlock(Grid *g) {
    char tmp = nextBlock;
    nextBlock = getNext();
    // first parameter is the current level (0)
    return charToBlock(0, tmp, g);
}

void Level0::setRandom(bool input, string file){
    (void)input;
    (void)file;
}

Level0::~Level0() {}
