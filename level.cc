#include "level.h"

Level::Level(int seed, char nextBlock) : seed{seed}, nextBlock{nextBlock} {}

char Level::returnNext() {
    return nextBlock;
}

Block *Level::charToBlock(int level, const char type, Grid *g) {
    if (type == 'S') return new sBlock{level, g};
    if (type == 'Z') return new zBlock{level, g};
    if (type == 'I') return new iBlock{level, g};
    if (type == 'T') return new tBlock{level, g};
    if (type == 'J') return new jBlock{level, g};
    if (type == 'L') return new lBlock{level, g};
    if (type == 'O') return new oBlock{level, g};
    return nullptr;
}

char Level::getNextNV() {
    return getNext();
}

Block *Level::createBlockNV(Grid *g) {
    return createBlock(g);
}

void Level::setRandomNV(bool input, std::string file) {
    setRandom(input, file);
}

Level::~Level() {}
