#include "level1.h"
#include <cstdlib>

using namespace std;


Level1::Level1(int seed, char nextBlock) : Level{seed, nextBlock} {
    // sets up types with appropriate probabilities
    vector<char> types{'J', 'J', 'Z', 'S', 'I', 'I', 'L', 'L', 'O', 'O', 'T', 'T'};
    blockTypes = types;
}


char Level1::getNext() {
    int index = rand() % (blockTypes.size());
    nextBlock = blockTypes.at(index);;
    return nextBlock;
}


Block *Level1::createBlock(Grid *g) {
    char tmp = nextBlock;
    nextBlock = getNext();
    return charToBlock(1, tmp, g);
}

void Level1::setRandom(bool input, string file) {
    (void)input;
    (void)file;
}


Level1::~Level1() {}
