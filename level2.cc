#include "level2.h"
#include <cstdlib>

using namespace std;

Level2::Level2(int seed, char nextBlock) : Level{seed, nextBlock} {
    vector<char> blocks {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
    blockTypes = blocks;
}

char Level2::getNext() {
    int index = rand() % (blockTypes.size());
    nextBlock = blockTypes.at(index);;
    return nextBlock;
}

Block *Level2::createBlock(Grid *g) {
    char tmp = nextBlock;
    nextBlock = getNext();
    return charToBlock(2, tmp, g);
}

void Level2::setRandom(bool input, string file) {
    (void)input;
    (void)file;
}

Level2::~Level2() {}
