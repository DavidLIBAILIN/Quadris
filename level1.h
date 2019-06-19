#ifndef LEVEL1_H
#define LEVEL1_h

#include "level.h"
#include <vector>

class Level1 : public Level{

    // contains names of blocks from which the create
    // method randomly chooses one
    std::vector<char> blockTypes;
    char getNext() override;
    Block *createBlock(Grid *g) override;
    void setRandom(bool input, std::string file = "") override;
 
public:

    Level1(int seed, char nextBlock = ' ');
    ~Level1() override;

};

#endif
