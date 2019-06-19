#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "tBlock.h"
#include "zBlock.h"

class Grid;
class Block;

class Level {

protected:

    int seed;
    // converts a char (eg 'Z') to appropriate block
    char nextBlock;
    virtual char getNext() = 0;
    virtual Block *createBlock(Grid *g) = 0;
    virtual void setRandom(bool input, std::string file = "") = 0;
    
public:

    Level(int seed, char nextBlock = ' ');
    char returnNext();
    Block *charToBlock(int level, const char type, Grid *g);
    char getNextNV();
    Block *createBlockNV(Grid *g);
    void setRandomNV(bool input, std::string file = "");
    virtual ~Level() = 0;

};

#endif
